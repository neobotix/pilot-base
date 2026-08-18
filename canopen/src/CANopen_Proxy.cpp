/*
 * CANopen_Proxy.cpp
 *
 *  Created on: Aug 19, 2025
 *      Author: jaw
 */

#include <pilot/base/canopen/CANopen_Proxy.h>


namespace pilot {
namespace base {
namespace canopen {


static std::string object_name(uint16_t index, uint8_t subindex){
	std::stringstream ss;
	ss << "0x" << std::hex << index << "." << static_cast<int>(subindex);
	return ss.str();
}


CANopen_Proxy::CANopen_Proxy(const std::string& _vnx_name)
	:	CANopen_ProxyBase(_vnx_name)
{
}


void CANopen_Proxy::init(){
	vnx::open_pipe(vnx_name, this, 100);
}


void CANopen_Proxy::main(){
	subscribe(input_can, 100);
	subscribe(input_pdo, 100);

	own_node.calculate_can_ids();
	for(auto &node : network){
		node.calculate_can_ids();
	}

	set_timer_millis(50, std::bind(&CANopen_Proxy::check_request_timeouts, this));
	if(sync_interval_ms > 0){
		set_timer_millis(sync_interval_ms, std::bind(&CANopen_Proxy::sync, this));
	}
	if(heartbeat_interval_ms > 0){
		set_timer_millis(heartbeat_interval_ms, std::bind(&CANopen_Proxy::heartbeat, this));
		heartbeat_sync_divider = 0;
	}

	if(activate_network){
		reset_network();
	}else{
		is_network_init = true;
		if(activate_network_operational){
			set_operational();
		}
		if(query_information){
			request_names();
		}
	}

	Super::main();

	if(shutdown_network){
		auto frame = node_t::module_control(nmt_command_e::GO_TO_STOPPED, 0);
		publish(frame, output_can);
	}
}


bool CANopen_Proxy::vnx_shutdown(){
	if(shutdown_delay_ms <= 0){
		return true;
	}
	set_timeout_millis(shutdown_delay_ms, std::bind(&CANopen_Proxy::exit, this));
	return false;
}


void CANopen_Proxy::reset_network(){
	log(INFO) << "Resetting network ...";
	is_network_init = false;
	node_states.clear();

	check_initialized();
	if(activate_network){
		if(init_timer){
			init_timer->reset();
		}else{
			init_timer = set_timer_millis(1000, std::bind(&CANopen_Proxy::check_initialized, this));
		}
	}
}


void CANopen_Proxy::upload_async(const uint32_t& node_id, const uint16_t& index, const uint8_t& subindex, const vnx::request_id_t& _request_id) const{
	std::shared_ptr<sdo_request_t> request;
	try{
		request = upload_internal(node_id, index, subindex);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->upload.callback = std::bind(&CANopen_Proxy::upload_async_return, this, _request_id, std::placeholders::_1);
	trigger_request(*request);
}


void CANopen_Proxy::download_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const std::vector<uint8_t> &data, const vnx::request_id_t &_request_id){
	std::shared_ptr<sdo_request_t> request;
	try{
		request = download_internal(node_id, index, subindex, data);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->download.callback = std::bind(&CANopen_Proxy::download_async_return, this, _request_id);
	trigger_request(*request);
}


void CANopen_Proxy::download_expedited_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const uint32_t &data, const uint32_t &num_bytes, const vnx::request_id_t &_request_id){
	std::shared_ptr<sdo_request_t> request;
	try{
		request = download_expedited_internal(node_id, index, subindex, data, num_bytes);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}

	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->download.callback = std::bind(&CANopen_Proxy::download_expedited_async_return, this, _request_id);
	trigger_request(*request);
}


void CANopen_Proxy::map_rpdo_async(const uint32_t &node_id, const uint32_t &pdo_type, const std::vector<object_address_t> &objects, const bool &rtr, const vnx::request_id_t &_request_id){
	uint32_t can_id;
	try{
		const auto &node = find_node(node_id);
		can_id = node.get_rx_pdo(pdo_type);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	const uint16_t pdo_comm = 0x1400 + pdo_type - 1;
	const uint16_t pdo_map = 0x1600 + pdo_type - 1;
	const uint32_t cob_entry = (rtr << 30) | ((can_id > 2047 ? 1 : 0) << 29) | can_id;
	const auto callback = std::bind(&CANopen_Proxy::map_rpdo_async_return, this, _request_id);
	const auto callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	map_pdo_internal(node_id, pdo_comm, pdo_map, cob_entry, objects, callback, callback_error_what);
}


void CANopen_Proxy::map_tpdo_async(const uint32_t &node_id, const uint32_t &pdo_type, const std::vector<object_address_t> &objects, const bool &rtr, const vnx::request_id_t &_request_id){
	uint32_t can_id;
	try{
		const auto &node = find_node(node_id);
		can_id = node.get_tx_pdo(pdo_type);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	const uint16_t pdo_comm = 0x1800 + pdo_type - 1;
	const uint16_t pdo_map = 0x1a00 + pdo_type - 1;
	const uint32_t cob_entry = (rtr << 30) | ((can_id > 2047 ? 1 : 0) << 29) | can_id;
	const auto callback = std::bind(&CANopen_Proxy::map_tpdo_async_return, this, _request_id);
	const auto callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	map_pdo_internal(node_id, pdo_comm, pdo_map, cob_entry, objects, callback, callback_error_what);
}


void CANopen_Proxy::pdo_sync_async(const uint32_t &node_id, const uint32_t &pdo_type, const uint8_t &sync_divider, const vnx::request_id_t &_request_id){
	if(pdo_type < 1 || pdo_type > 4){
		vnx_async_return_ex_what(_request_id, "Invalid PDO type");
		return;
	}
	const uint16_t index = 0x1800 + pdo_type - 1;
	const uint8_t subindex = 2;
	std::shared_ptr<sdo_request_t> request;
	try{
		// transmission type SYNC: pdo_comm.2  =  sync_divider
		request = download_expedited_internal(node_id, index, subindex, sync_divider, 4);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->download.callback = std::bind(&CANopen_Proxy::pdo_sync_async_return, this, _request_id);
	trigger_request(*request);
}


void CANopen_Proxy::handle(std::shared_ptr<const CAN_Frame> sample){
	if(sample->id == own_node.rx_sdo){
		const auto ccs = own_node.get_sdo_ccs(*sample);
		if(ccs != sdo_ccs_e::ABORT){
			uint16_t index = 0;
			uint8_t subindex = 0;
			if(ccs == sdo_ccs_e::INIT_DOWNLOAD || ccs == sdo_ccs_e::INIT_UPLOAD || ccs == sdo_ccs_e::SEGMENT_UPLOAD){
				index = (sample->data[2] << 8) | sample->data[1];
				subindex = sample->data[3];
			}
			auto frame = own_node.abort_server(index, subindex, sdo_error_e::GENERAL_ERROR);
			publish(frame, output_can);
		}
	}
	for(auto &node : network){
		const auto pdo_type = node.find_tx_pdo_type(sample->id);
		if(pdo_type > 0){
			auto out = PDO::create();
			out->node_id = node.id;
			out->type = pdo_type;
			out->time = sample->time;
			out->payload.resize(sample->size);
			for(size_t i=0; i<sample->size; i++){
				out->payload[i] = sample->data[i];
			}
			publish(out, output_pdo);
		}else if(sample->id == node.tx_sdo){
			const auto scs = node.get_sdo_scs(*sample);
			uint16_t index = 0;
			uint8_t subindex = 0;
			if(scs == sdo_scs_e::ABORT || scs == sdo_scs_e::INIT_UPLOAD_RESPONSE || scs == sdo_scs_e::INIT_DOWNLOAD_RESPONSE){
				index = (sample->data[2] << 8) | sample->data[1];
				subindex = sample->data[3];
			}else if(scs == sdo_scs_e::SEGMENT_UPLOAD_RESPONSE || scs == sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE){
				const auto find = node_states.find(node.id);
				if(find != node_states.end()){
					if(scs == sdo_scs_e::SEGMENT_UPLOAD_RESPONSE){
						index = find->second.active_upload.first;
						subindex = find->second.active_upload.second;
					}else if(scs == sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE){
						index = find->second.active_download.first;
						subindex = find->second.active_download.second;
					}
				}
			}
			const auto find = sdo_requests.find(std::make_tuple(node.id, index, subindex));
			if(find != sdo_requests.end()){
				auto &request = find->second;
				if(scs == sdo_scs_e::ABORT){
					const auto error = node.get_sdo_error(*sample);
					const std::string message = "SDO request on object " + object_name(request.index, request.subindex) + " of node " + std::to_string(request.node_id) + " failed with: " + vnx::to_string_value(error);
					if(request.callback_error_what){
						request.callback_error_what(message);
					}else{
						log(WARN) << message;
					}
					sdo_requests.erase(find);
				}else if(scs == sdo_scs_e::INIT_UPLOAD_RESPONSE || scs == sdo_scs_e::SEGMENT_UPLOAD_RESPONSE){
					const auto answer = node.get_uploaded_data(*sample);
					const bool toggle = ((sample->data[0] >> 4) & 0x1);
					if(scs == sdo_scs_e::SEGMENT_UPLOAD_RESPONSE && toggle != request.expected_toggle){
						auto abort_frame = node.abort_client(index, subindex, sdo_error_e::TOGGLE_BIT_ERROR);
						publish(abort_frame, output_can);
						const std::string message = "Toggle bit error";
						if(request.callback_error_what){
							request.callback_error_what(message);
						}else{
							log(WARN) << message;
						}
						sdo_requests.erase(find);
					}else if(answer.second){
						// upload finished
						request.upload.data.insert(request.upload.data.end(), answer.first.begin(), answer.first.end());
						if(request.upload.callback){
							request.upload.callback(request.upload.data);
						}
						if(index == 0x1008 && subindex == 0){
							const std::string device_name(reinterpret_cast<const char *>(request.upload.data.data()), request.upload.data.size());
							node_states[node.id].name = device_name;
						}
						auto next = request.next;
						sdo_requests.erase(find);
						if(next){
							trigger_request(*next);
						}
					}else{
						// segmented upload initiated or continued
						if(scs == sdo_scs_e::SEGMENT_UPLOAD_RESPONSE){
							request.upload.data.insert(request.upload.data.end(), answer.first.begin(), answer.first.end());
							request.expected_toggle = !request.expected_toggle;
						}
						node_states[node.id].active_upload = {index, subindex};
						if(!request.upload.frames.first || !request.upload.frames.second){
							request.upload.frames = node.upload_segment_request(index, subindex);
						}
						auto frame = request.upload.toggle ? request.upload.frames.second : request.upload.frames.first;
						request.upload.toggle = !request.upload.toggle;
						publish(frame, output_can);
					}
				}else if(scs == sdo_scs_e::INIT_DOWNLOAD_RESPONSE || scs == sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE){
					const bool toggle = ((sample->data[0] >> 4) & 0x1);
					if(scs == sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE && toggle != request.expected_toggle){
						auto abort_frame = node.abort_client(index, subindex, sdo_error_e::TOGGLE_BIT_ERROR);
						publish(abort_frame, output_can);
						const std::string message = "Toggle bit error";
						if(request.callback_error_what){
							request.callback_error_what(message);
						}else{
							log(WARN) << message;
						}
						sdo_requests.erase(find);
					}else if(request.download.index < request.download.frames.size()){
						// segmented download initiated or continued
						node_states[node.id].active_download = {index, subindex};
						request.expected_toggle = !request.expected_toggle;
						publish(request.download.frames[request.download.index++], output_can);
					}else{
						// download finished
						if(request.download.callback){
							request.download.callback();
						}
						auto next = request.next;
						sdo_requests.erase(find);
						if(next){
							trigger_request(*next);
						}
					}
				}
			}
		}else if(sample->id == node.emcy){
			const auto code = node.handle_emcy(*sample);
			if(code != emcy_code_e::NO_ERROR){
				log(WARN) << "Node " << node.id << " EMCY: " << code;
			}
		}else if(sample->id == node.nmt){
			node_states[node.id].state = node.get_nmt_state(*sample);
		}
	}
}


void CANopen_Proxy::handle(std::shared_ptr<const PDO> sample){
	const auto &node = find_node(sample->node_id);
	const auto can_id = node.get_rx_pdo(sample->type);

	auto out = CAN_Frame::create();
	out->time = sample->time;
	out->id = can_id;
	const size_t size = std::min<size_t>(sample->payload.size(), out->data.size());
	out->size = size;
	for(size_t i=0; i<size; i++){
		out->data[i] = sample->payload[i];
	}
	publish(out, output_can);
}


const node_t &CANopen_Proxy::find_node(uint32_t node_id) const{
	for(const auto &node : network){
		if(node.id == node_id){
			return node;
		}
	}
	throw std::logic_error("No node with ID " + std::to_string(node_id));
}


std::shared_ptr<CANopen_Proxy::sdo_request_t> CANopen_Proxy::upload_internal(uint32_t node_id, uint16_t index, uint8_t subindex) const{
	auto frame = find_node(node_id).upload_request(index, subindex);
	auto request = std::make_shared<sdo_request_t>();
	request->node_id = node_id;
	request->index = index;
	request->subindex = subindex;
	if(sdo_timeout_ms > 0){
		request->timeout = vnx::get_wall_time_micros() + sdo_timeout_ms*1000;
	}
	request->initial_frame = frame;
	return request;
}


std::shared_ptr<CANopen_Proxy::sdo_request_t> CANopen_Proxy::download_internal(uint32_t node_id, uint16_t index, uint8_t subindex, const std::vector<uint8_t> &data) const{
	std::shared_ptr<const CAN_Frame> expedited_frame;
	std::vector<std::shared_ptr<const CAN_Frame>> segmented_frames;
	{
		const auto &node = find_node(node_id);
		if(data.size() <= 4){
			// expedited transfer
			uint32_t int_data = 0;
			for(size_t i=0; i<data.size(); i++){
				int_data |= (data[i] << (8*i));
			}
			expedited_frame = node.download_expedited(index, subindex, int_data, data.size());
		}else{
			// segmented transfer
			segmented_frames = node.download_segmented(index, subindex, data);
		}
	}

	auto request = std::make_shared<sdo_request_t>();
	request->node_id = node_id;
	request->index = index;
	request->subindex = subindex;
	if(sdo_timeout_ms > 0){
		request->timeout = vnx::get_wall_time_micros() + sdo_timeout_ms*1000;
	}
	if(expedited_frame){
		request->download.frames.push_back(expedited_frame);
	}else{
		request->download.frames = segmented_frames;
	}
	request->initial_frame = request->download.frames.at(0);
	request->download.index = 1;
	return request;
}


std::shared_ptr<CANopen_Proxy::sdo_request_t> CANopen_Proxy::download_expedited_internal(uint32_t node_id, uint16_t index, uint8_t subindex, uint32_t data, uint32_t num_bytes) const{
	std::vector<uint8_t> vec_data;
	for(size_t i=0; i<num_bytes; i++){
		vec_data.push_back(data >> (8*i));
	}
	return download_internal(node_id, index, subindex, vec_data);
}


void CANopen_Proxy::map_pdo_internal(uint32_t node_id, uint16_t pdo_comm, uint16_t pdo_map, uint32_t cob_entry, const std::vector<object_address_t> &objects, const std::function<void()> &callback, const std::function<void(const std::string &)> &callback_error_what) const{
	// disable PDO: pdo_comm.1  |=  (1 << 31)
	auto first_request = download_expedited_internal(node_id, pdo_comm, 1, (1 << 31) | cob_entry, 4);
	first_request->callback_error_what = callback_error_what;
	auto current_request = first_request;

	// destroy PDO mapping: pdo_map.0  =  0
	current_request->next = download_expedited_internal(node_id, pdo_map, 0, 0, 4);
	current_request = current_request->next;
	current_request->callback_error_what = callback_error_what;

	for(size_t i=0; i<objects.size(); i++){
		const auto &object = objects[i];
		const uint32_t value = (object.index << 16) | (object.subindex << 8) | object.num_bits;
		// map object to index: pdo_map.i  =  value
		current_request->next = download_expedited_internal(node_id, pdo_map, i, value, 4);
		current_request = current_request->next;
		current_request->callback_error_what = callback_error_what;
	}

	// activate mapped objects: pdo_map.0  =  objects.size()
	current_request->next = download_expedited_internal(node_id, pdo_map, 0, objects.size(), 4);
	current_request = current_request->next;
	current_request->callback_error_what = callback_error_what;

	// enable PDO: pdo_comm.1  &=  ~(1 << 31)
	current_request->next = download_expedited_internal(node_id, pdo_comm, 1, cob_entry, 4);
	current_request = current_request->next;
	current_request->callback_error_what = callback_error_what;
	current_request->download.callback = callback;

	trigger_request(*first_request);
}


void CANopen_Proxy::trigger_request(const sdo_request_t &request) const{
	const auto key = std::make_tuple(request.node_id, request.index, request.subindex);
	const size_t size_before = sdo_requests.size();
	auto &entry = sdo_requests[key];
	if(sdo_requests.size() == size_before){
		// request already exists, cancel
		try{
			const auto &node = find_node(request.node_id);
			auto frame = node.abort_client(request.index, request.subindex, sdo_error_e::DATA_TRANSFER);
			publish(frame, output_can);
		}catch(const std::exception &){
		}
		const std::string message = "SDO request on object " + object_name(entry.index, entry.subindex) + " of node " + std::to_string(entry.node_id) + " superseded";
		if(entry.callback_error_what){
			entry.callback_error_what(message);
		}else{
			log(WARN) << message;
		}
	}
	entry = request;
	publish(request.initial_frame, output_can);
}


void CANopen_Proxy::check_request_timeouts(){
	const auto now = vnx::get_wall_time_micros();
	for(auto iter=sdo_requests.begin(); iter!=sdo_requests.end(); /* no iter */){
		const auto &request = iter->second;
		if(request.timeout > 0 && request.timeout <= now){
			try{
				const auto &node = find_node(request.node_id);
				auto frame = node.abort_client(request.index, request.subindex, sdo_error_e::TIMEOUT);
				publish(frame, output_can);
			}catch(const std::exception &){
			}
			const std::string message = "Timeout for SDO request on object " + object_name(request.index, request.subindex) + " of node " + std::to_string(request.node_id);
			if(request.callback_error_what){
				request.callback_error_what(message);
			}else{
				log(WARN) << message;
			}
			iter = sdo_requests.erase(iter);
		}else{
			iter++;
		}
	}
}


void CANopen_Proxy::check_initialized(){
	bool empty = true;
	for(const auto &entry : node_states){
		if(entry.second.state){
			empty = false;
		}
	}

	bool alive = true;
	if(empty){
		alive = false;
		auto frame = node_t::module_control(nmt_command_e::GO_TO_RESET_NODE, 0);
		publish(frame, output_can);
	}else{
		for(const auto &node : network){
			if(node.is_virtual){
				continue;
			}
			const auto find = node_states.find(node.id);
			if(find == node_states.end() || !find->second.state){
				alive = false;
				auto frame = node_t::module_control(nmt_command_e::GO_TO_RESET_NODE, node.id);
				publish(frame, output_can);
			}
		}
	}

	if(alive){
		log(INFO) << "All nodes alive";
		is_network_init = true;
		if(activate_network_operational){
			set_operational();
		}
		if(query_information){
			request_names();
		}
		if(init_timer){
			init_timer->stop();
		}
	}
}


void CANopen_Proxy::set_operational(){
	auto frame = node_t::module_control(nmt_command_e::GO_TO_OPERATIONAL, 0);
	publish(frame, output_can);
}


void CANopen_Proxy::request_names(){
	const uint16_t index = 0x1008;
	const uint8_t subindex = 0;
	for(const auto &node : network){
		if(node.is_virtual){
			continue;
		}
		std::shared_ptr<sdo_request_t> request;
		try{
			request = upload_internal(node.id, index, subindex);
		}catch(const std::exception &err){
		}
		if(request){
			trigger_request(*request);
		}
	}
}


void CANopen_Proxy::sync() const{
	auto out = node_t::sync();
	publish(out, output_can);
	sync_counter++;
	if(heartbeat_sync_divider > 0 && (sync_counter % heartbeat_sync_divider) == 0){
		heartbeat();
	}
}


void CANopen_Proxy::heartbeat() const{
	auto out = own_node.heartbeat(nmt_state_e::OPERATIONAL);
	publish(out, output_can);
}


} // canopen
} // base
} // pilot


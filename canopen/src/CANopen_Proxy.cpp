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

	is_network_init = true;
	if(activate_network){
		is_network_init = false;
		init_timer = set_timer_millis(1000, std::bind(&CANopen_Proxy::network_reset, this));
	}
	set_timer_millis(50, std::bind(&CANopen_Proxy::check_request_timeouts, this));
	if(sync_interval_ms > 0){
		set_timer_millis(sync_interval_ms, std::bind(&CANopen_Proxy::sync, this));
	}
	if(heartbeat_interval_ms > 0){
		set_timer_millis(heartbeat_interval_ms, std::bind(&CANopen_Proxy::heartbeat, this));
	}

	Super::main();
}


void CANopen_Proxy::upload_async(const uint32_t& node_id, const uint16_t& index, const uint8_t& subindex, const int32_t &timeout_ms, const vnx::request_id_t& _request_id) const{
	std::shared_ptr<sdo_request_t> request;
	try{
		request = upload_internal(node_id, index, subindex, timeout_ms);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->upload.callback = std::bind(&CANopen_Proxy::upload_async_return, this, _request_id, std::placeholders::_1);
	sdo_requests[std::make_tuple(node_id, index, subindex)] = *request;
	publish(request->initial_frame, output_can);
}


void CANopen_Proxy::download_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const std::vector<uint8_t> &data, const int32_t &timeout_ms, const vnx::request_id_t &_request_id){
	std::shared_ptr<sdo_request_t> request;
	try{
		request = download_internal(node_id, index, subindex, data, timeout_ms);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->download.callback = std::bind(&CANopen_Proxy::download_async_return, this, _request_id);
	sdo_requests[std::make_tuple(node_id, index, subindex)] = *request;
	publish(request->initial_frame, output_can);
}


void CANopen_Proxy::download_expedited_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const uint32_t &data, const uint32_t &num_bytes, const int32_t &timeout_ms, const vnx::request_id_t &_request_id){
	std::shared_ptr<sdo_request_t> request;
	try{
		request = download_expedited_internal(node_id, index, subindex, data, num_bytes, timeout_ms);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}

	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->download.callback = std::bind(&CANopen_Proxy::download_expedited_async_return, this, _request_id);
	sdo_requests[std::make_tuple(node_id, index, subindex)] = *request;
	publish(request->initial_frame, output_can);
}


void CANopen_Proxy::map_pdo_async(const uint32_t &node_id, const uint32_t &pdo_type, const std::vector<object_entry_t> &objects, const bool &rtr, const int32_t &timeout_ms, const vnx::request_id_t &_request_id){
	if(pdo_type < 1 || pdo_type > 4){
		vnx_async_return_ex_what(_request_id, "Invalid PDO type");
		return;
	}
	uint32_t can_id;
	try{
		const auto &node = find_node(node_id);
		can_id = pdo_type==1 ? node.tx_pdo_1 : pdo_type==2 ? node.tx_pdo_2 : pdo_type==3 ? node.tx_pdo_3 : node.tx_pdo_4;
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	const uint16_t pdo_comm = 0x1800 + pdo_type - 1;
	const uint16_t pdo_map = 0x1a00 + pdo_type - 1;
	const uint32_t cob_entry = (rtr << 30) | ((can_id > 2047 ? 1 : 0) << 29) | can_id;
	auto callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);

	// disable PDO: pdo_comm.1  |=  (1 << 31)
	auto first_request = download_expedited_internal(node_id, pdo_comm, 1, (1 << 31) | cob_entry, 4, timeout_ms);
	first_request->callback_error_what = callback_error_what;
	auto current_request = first_request;

	// destroy PDO mapping: pdo_map.0  =  0
	current_request->next = download_expedited_internal(node_id, pdo_map, 0, 0, 4, timeout_ms);
	current_request = current_request->next;
	current_request->callback_error_what = callback_error_what;

	for(size_t i=0; i<objects.size(); i++){
		const auto &object = objects[i];
		const uint32_t value = (object.index << 16) | (object.subindex << 8) | (object.num_bytes*8);
		// map object to index: pdo_map.i  =  value
		current_request->next = download_expedited_internal(node_id, pdo_map, i, value, 4, timeout_ms);
		current_request = current_request->next;
		current_request->callback_error_what = callback_error_what;
	}

	// activate mapped objects: pdo_map.0  =  objects.size()
	current_request->next = download_expedited_internal(node_id, pdo_map, 0, objects.size(), 4, timeout_ms);
	current_request = current_request->next;
	current_request->callback_error_what = callback_error_what;

	// enable PDO: pdo_comm.1  &=  ~(1 << 31)
	current_request->next = download_expedited_internal(node_id, pdo_comm, 1, cob_entry, 4, timeout_ms);
	current_request = current_request->next;
	current_request->callback_error_what = callback_error_what;
	current_request->download.callback = std::bind(&CANopen_Proxy::map_pdo_async_return, this, _request_id);

	sdo_requests[std::make_tuple(first_request->node_id, first_request->index, first_request->subindex)] = *first_request;
	publish(first_request->initial_frame, output_can);
}


void CANopen_Proxy::pdo_sync_async(const uint32_t &node_id, const uint32_t &pdo_type, const uint8_t &sync_divider, const int32_t &timeout_ms, const vnx::request_id_t &_request_id){
	if(pdo_type < 1 || pdo_type > 4){
		vnx_async_return_ex_what(_request_id, "Invalid PDO type");
		return;
	}
	const uint16_t index = 0x1800 + pdo_type - 1;
	const uint8_t subindex = 2;
	std::shared_ptr<sdo_request_t> request;
	try{
		// transmission type SYNC: pdo_comm.2  =  sync_divider
		request = download_expedited_internal(node_id, index, subindex, sync_divider, 4, timeout_ms);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	request->callback_error_what = std::bind(&CANopen_Proxy::vnx_async_return_ex_what, this, _request_id, std::placeholders::_1);
	request->download.callback = std::bind(&CANopen_Proxy::pdo_sync_async_return, this, _request_id);
	sdo_requests[std::make_tuple(node_id, index, subindex)] = *request;
	publish(request->initial_frame, output_can);
}


void CANopen_Proxy::handle(std::shared_ptr<const CAN_Frame> sample){
	if(sample->id == own_node.rx_sdo){
		// TODO: answer?
	}
	for(auto &node : network){
		const bool is_pdo_1 = (sample->id == node.tx_pdo_1);
		const bool is_pdo_2 = (sample->id == node.tx_pdo_2);
		const bool is_pdo_3 = (sample->id == node.tx_pdo_3);
		const bool is_pdo_4 = (sample->id == node.tx_pdo_4);
		if(is_pdo_1 || is_pdo_2 || is_pdo_3 || is_pdo_4){
			auto out = PDO::create();
			out->node_id = node.id;
			out->type = is_pdo_1 ? 1 : is_pdo_2 ? 2 : is_pdo_3 ? 3 : 4;
			out->time = sample->time;
			out->payload.resize(sample->size);
			for(size_t i=0; i<sample->size; i++){
				out->payload[i] = sample->data[i];
			}
			publish(out, output_pdo);
		}else if(sample->id == node.tx_sdo){
			const uint16_t index = (sample->data[2] << 8) | sample->data[1];
			const uint8_t subindex = sample->data[3];
			const auto find = sdo_requests.find(std::make_tuple(node.id, index, subindex));
			if(find != sdo_requests.end()){
				auto &request = find->second;
				const auto scs = node.get_sdo_scs(*sample);
				if(scs == sdo_scs_e::ABORT){
					const auto error = node.get_sdo_error(*sample);
					request.callback_error_what("SDO request on object " + object_name(request.index, request.subindex) + " of node " + std::to_string(request.node_id) + " failed with: " + vnx::to_string_value(error));
					sdo_requests.erase(find);
				}else if(scs == sdo_scs_e::INIT_UPLOAD_RESPONSE){
					const auto answer = node.get_uploaded_data(*sample);
					if(answer.second){
						// expedited transfer, upload finished
						if(request.upload.callback){
							request.upload.callback(answer.first);
						}
						auto next = request.next;
						sdo_requests.erase(find);
						if(next){
							sdo_requests[std::make_tuple(next->node_id, next->index, next->subindex)] = *next;
							publish(next->initial_frame, output_can);
						}
					}else{
						// init of segmented transfer
						uint32_t size = 0;
						for(size_t i=0; i<answer.first.size(); i++){
							size |= (answer.first[i] << (8*i));
						}
						request.upload.frames = node.upload_segment_request(index, subindex);
						auto frame = request.upload.toggle ? request.upload.frames.first : request.upload.frames.second;
						request.upload.toggle = !request.upload.toggle;
						publish(frame, output_can);
					}
				}else if(scs == sdo_scs_e::SEGMENT_UPLOAD_RESPONSE){
					const auto answer = node.get_uploaded_data(*sample);
					request.upload.data.insert(request.upload.data.end(), answer.first.begin(), answer.first.end());
					if(answer.second){
						if(request.upload.callback){
							request.upload.callback(request.upload.data);
						}
						auto next = request.next;
						sdo_requests.erase(find);
						if(next){
							sdo_requests[std::make_tuple(next->node_id, next->index, next->subindex)] = *next;
							publish(next->initial_frame, output_can);
						}
					}else{
						auto frame = request.upload.toggle ? request.upload.frames.first : request.upload.frames.second;
						request.upload.toggle = !request.upload.toggle;
						publish(frame, output_can);
					}
				}else if(scs == sdo_scs_e::INIT_DOWNLOAD_RESPONSE){
					if(request.download.index < request.download.frames.size()){
						// segmented download initiated
						publish(request.download.frames[request.download.index++], output_can);
					}else{
						// expedited download acknowledged
						if(request.download.callback){
							request.download.callback();
						}
						auto next = request.next;
						sdo_requests.erase(find);
						if(next){
							sdo_requests[std::make_tuple(next->node_id, next->index, next->subindex)] = *next;
							publish(next->initial_frame, output_can);
						}
					}
				}else if(scs == sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE){
					if(request.download.index < request.download.frames.size()){
						// continue segmented download
						publish(request.download.frames[request.download.index++], output_can);
					}else{
						// segmented download finished
						if(request.download.callback){
							request.download.callback();
						}
						auto next = request.next;
						sdo_requests.erase(find);
						if(next){
							sdo_requests[std::make_tuple(next->node_id, next->index, next->subindex)] = *next;
							publish(next->initial_frame, output_can);
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
			node_states[node.id] = node.get_nmt_state(*sample);
			if(!is_network_init && node_states.size() == network.size()){
				log(INFO) << "All nodes alive";
				if(activate_network_operational){
					auto frame = node_t::module_control(nmt_command_e::GO_TO_OPERATIONAL, 0);
					publish(frame, output_can);
				}
				is_network_init = true;
				if(init_timer){
					init_timer->stop();
				}
			}
		}
	}
}


void CANopen_Proxy::handle(std::shared_ptr<const PDO> sample){
	const auto &node = find_node(sample->node_id);
	uint32_t can_id = 0;
	switch(sample->type){
	case 1:
		can_id = node.rx_pdo_1;
		break;
	case 2:
		can_id = node.rx_pdo_2;
		break;
	case 3:
		can_id = node.rx_pdo_3;
		break;
	case 4:
		can_id = node.rx_pdo_4;
		break;
	default:
		throw std::logic_error("Invalid PDO type " + std::to_string(sample->type));
	}

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


std::shared_ptr<CANopen_Proxy::sdo_request_t> CANopen_Proxy::upload_internal(uint32_t node_id, uint16_t index, uint8_t subindex, int32_t timeout_ms) const{
	auto frame = find_node(node_id).upload_request(index, subindex);
	auto request = std::make_shared<sdo_request_t>();
	request->node_id = node_id;
	request->index = index;
	request->subindex = subindex;
	if(timeout_ms > 0){
		request->timeout = vnx::get_wall_time_micros() + timeout_ms*1000;
	}
	request->initial_frame = frame;
	return request;
}


std::shared_ptr<CANopen_Proxy::sdo_request_t> CANopen_Proxy::download_internal(uint32_t node_id, uint16_t index, uint8_t subindex, const std::vector<uint8_t> &data, int32_t timeout_ms) const{
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
	if(timeout_ms > 0){
		request->timeout = vnx::get_wall_time_micros() + timeout_ms*1000;
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


std::shared_ptr<CANopen_Proxy::sdo_request_t> CANopen_Proxy::download_expedited_internal(uint32_t node_id, uint16_t index, uint8_t subindex, uint32_t data, uint32_t num_bytes, int32_t timeout_ms) const{
	std::vector<uint8_t> vec_data;
	for(size_t i=0; i<num_bytes; i++){
		vec_data.push_back(data >> (8*i));
	}
	return download_internal(node_id, index, subindex, vec_data, timeout_ms);
}


void CANopen_Proxy::check_request_timeouts(){
	const auto now = vnx::get_wall_time_micros();
	for(auto iter=sdo_requests.begin(); iter!=sdo_requests.end(); /* no iter */){
		bool itered = false;
		const auto &request = iter->second;
		if(request.timeout > 0 && request.timeout <= now){
			request.callback_error_what("Timeout for SDO request on object " + object_name(request.index, request.subindex) + " of node " + std::to_string(request.node_id));
			iter = sdo_requests.erase(iter);
			itered = true;
		}
		if(!itered){
			iter++;
		}
	}
}


void CANopen_Proxy::network_reset(){
	log(INFO) << "Resetting network ...";
	node_states.clear();
	auto frame = node_t::module_control(nmt_command_e::GO_TO_RESET_NODE, 0);
	publish(frame, output_can);
}


void CANopen_Proxy::sync() const{
	auto out = node_t::sync();
	publish(out, output_can);
}


void CANopen_Proxy::heartbeat() const{
	auto out = own_node.heartbeat(nmt_state_e::OPERATIONAL);
	publish(out, output_can);
}


} // canopen
} // base
} // pilot


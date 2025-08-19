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

	if(sync_interval_ms > 0){
		set_timer_millis(sync_interval_ms, std::bind(&CANopen_Proxy::sync, this));
	}
	if(heartbeat_interval_ms > 0){
		set_timer_millis(heartbeat_interval_ms, std::bind(&CANopen_Proxy::heartbeat, this));
	}

	Super::main();
}


void CANopen_Proxy::upload_async(const uint32_t& node_id, const uint16_t& index, const uint8_t& subindex, const vnx::request_id_t& _request_id) const{
	std::shared_ptr<const CAN_Frame> frame;
	try{
		frame = find_node(node_id).upload_request(index, subindex);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}
	auto &request = sdo_requests[std::make_tuple(node_id, index, subindex)];
	request.request_id = _request_id;
	request.node_id = node_id;
	request.index = index;
	request.subindex = subindex;

	publish(frame, output_can);
}


void CANopen_Proxy::download_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const std::vector<uint8_t> &data, const vnx::request_id_t &_request_id){
	std::shared_ptr<const CAN_Frame> expedited_frame;
	std::vector<std::shared_ptr<const CAN_Frame>> segmented_frames;
	try{
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
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}

	auto &request = sdo_requests[std::make_tuple(node_id, index, subindex)];
	request.request_id = _request_id;
	request.node_id = node_id;
	request.index = index;
	request.subindex = subindex;
	request.download.segmented_frames = segmented_frames;

	if(expedited_frame){
		publish(expedited_frame, output_can);
	}else if(!request.download.segmented_frames.empty()){
		publish(request.download.segmented_frames[0], output_can);
		request.download.index = 1;
	}
}


void CANopen_Proxy::download_expedited_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const uint32_t &data, const uint32_t &num_bytes, const vnx::request_id_t &_request_id){
	std::shared_ptr<const CAN_Frame> frame;
	try{
		const auto &node = find_node(node_id);
		frame = node.download_expedited(index, subindex, data, num_bytes);
	}catch(const std::exception &err){
		vnx_async_return_ex_what(_request_id, err.what());
		return;
	}

	auto &request = sdo_requests[std::make_tuple(node_id, index, subindex)];
	request.request_id = _request_id;
	request.node_id = node_id;
	request.index = index;
	request.subindex = subindex;
	request.download.expedited_request = true;

	publish(frame, output_can);
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
					vnx_async_return_ex_what(request.request_id, "SDO request failed with " + vnx::to_string_value(error));
					sdo_requests.erase(find);
				}else if(scs == sdo_scs_e::INIT_UPLOAD_RESPONSE){
					const auto answer = node.get_uploaded_data(*sample);
					if(answer.second){
						// expedited transfer, upload finished
						upload_async_return(request.request_id, answer.first);
						sdo_requests.erase(find);
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
						upload_async_return(request.request_id, request.upload.data);
						sdo_requests.erase(find);
					}else{
						auto frame = request.upload.toggle ? request.upload.frames.first : request.upload.frames.second;
						request.upload.toggle = !request.upload.toggle;
						publish(frame, output_can);
					}
				}else if(scs == sdo_scs_e::INIT_DOWNLOAD_RESPONSE){
					if(request.download.segmented_frames.empty()){
						// acknowledged expedited transfer
						if(request.download.expedited_request){
							download_expedited_async_return(request.request_id);
						}else{
							download_async_return(request.request_id);
						}
						sdo_requests.erase(find);
					}else if(request.download.index < request.download.segmented_frames.size()){
						publish(request.download.segmented_frames[request.download.index++], output_can);
					}
				}else if(scs == sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE){
					if(request.download.index < request.download.segmented_frames.size()){
						publish(request.download.segmented_frames[request.download.index++], output_can);
					}else{
						download_async_return(request.request_id);
						sdo_requests.erase(find);
					}
				}
			}
		}else if(sample->id == node.emcy){
			const auto code = node.handle_emcy(*sample);
			// TODO
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


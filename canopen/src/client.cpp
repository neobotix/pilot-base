#include <pilot/base/canopen/node_t.hxx>
#include <pilot/base/socketcan_options_t.hxx>
#ifdef _WIN32
#include <pilot/base/CAN_PeakUSB.h>
#include <pilot/base/CAN_Kvaser.h>
#else
#include <pilot/base/CAN_Socket.h>
#endif
#include <vnx/Input.hpp>
#include <vnx/Output.hpp>



enum class opmode_e{
	NONE,
	SYNC,
	MODULE_CONTROL,
	HEARTBEAT,
	UPLOAD,
	DOWNLOAD,
	DOWNLOAD_SEGMENTED,
	ABORT,
};


unsigned long str_to_int(const std::string &str){
	if(str.rfind("0x", 0) != std::string::npos){
		// hex number
		return std::stoul(str, NULL, 16);
	}else{
		//decimal number
		return std::stoul(str);
	}
}


void list_enum_values(const vnx::TypeCode *type_code, std::ostream &out){
	bool first_one = true;
	for(const auto &entry : type_code->enum_map){
		if(!first_one){
			out << ", ";
		}
		out << entry.second;
		first_one = false;
	}
}


void usage(const std::string &cmd0){
	std::cout << "Usage:" << std::endl;
	std::cout << "    " << cmd0 << " [OPTIONS] sync" << std::endl;
	std::cout << "    " << cmd0 << " [OPTIONS] module-control <node-id> <nmt-command>" << std::endl;
	std::cout << "    " << cmd0 << " [OPTIONS] heartbeat <node-id> <nmt-state>" << std::endl;
	std::cout << "    " << cmd0 << " [OPTIONS] upload <node-id> <index> <subindex>" << std::endl;
	std::cout << "    " << cmd0 << " [OPTIONS] download <node-id> <index> <subindex> <size> <data>" << std::endl;
	std::cout << "    " << cmd0 << " [OPTIONS] download-segmented <node-id> <index> <subindex> <byte_1> [byte_2 [byte_3 ...]]" << std::endl;
	std::cout << "    " << cmd0 << " [OPTIONS] abort <node-id> <index> <subindex> <sdo-error>" << std::endl;
	std::cout << "where OPTIONS may be zero, one or more of the following" << std::endl;
#ifdef _WIN32
	std::cout << "    -b <baudrate>        - give the baud rate of the CAN bus in symbols/s" << std::endl;
	std::cout << "                           default is 1000000" << std::endl;
#else
	std::cout << "    -d <device>          - set the location of the CAN device" << std::endl;
	std::cout << "                           default is can0" << std::endl;
#endif
	std::cout << std::endl;
	std::cout << "Upload means reading from the device, download means writing to the device." << std::endl;
	std::cout << "Numbers can be given in decimal (1234) or in hex (0x4d2)." << std::endl;
	std::cout << "<nmt-command> is one of ";
	list_enum_values(pilot::base::canopen::nmt_command_e::static_get_type_code(), std::cout);
	std::cout << std::endl;
	std::cout << "<nmt-state> is one of ";
	list_enum_values(pilot::base::canopen::nmt_state_e::static_get_type_code(), std::cout);
	std::cout << std::endl;
	std::cout << "<sdo-error> is one of ";
	list_enum_values(pilot::base::canopen::sdo_error_e::static_get_type_code(), std::cout);
	std::cout << std::endl;
}


std::vector<std::string>::const_iterator parse_command(const std::vector<std::string> &args, opmode_e &opmode, int &baud_rate, std::string &device){
	baud_rate = 1000000;
	device = "can0";

	auto iter = args.begin();
	iter++;
	while(iter != args.end()){
		const auto &token = *iter;
		if(token == "sync"){
			opmode = opmode_e::SYNC;
			return ++iter;
		}else if(token == "module-control"){
			opmode = opmode_e::MODULE_CONTROL;
			return ++iter;
		}else if(token == "heartbeat"){
			opmode = opmode_e::HEARTBEAT;
			return ++iter;
		}else if(token == "upload"){
			opmode = opmode_e::UPLOAD;
			return ++iter;
		}else if(token == "download"){
			opmode = opmode_e::DOWNLOAD;
			return ++iter;
		}else if(token == "download-segmented"){
			opmode = opmode_e::DOWNLOAD_SEGMENTED;
			return ++iter;
		}else if(token == "abort"){
			opmode = opmode_e::ABORT;
			return ++iter;
#ifdef _WIN32
		}else if(token == "-b"){
			iter++;
			if(iter == args.end()){
				throw std::logic_error("Unterminated option");
			}
			baud_rate = str_to_int(*iter);
			iter++;
#else
		}else if(token == "-d"){
			iter++;
			if(iter == args.end()){
				throw std::logic_error("Unterminated option");
			}
			device = *iter;
			iter++;
#endif
		}else{
			throw std::logic_error("Unexpected command line option: " + *iter);
		}
	}
	return iter;
}


void parse_command_empty(std::vector<std::string>::const_iterator iter, std::vector<std::string>::const_iterator end){
	if(iter != end){
		throw std::logic_error("Unexpected command line option: " + *iter);
	}
}


void parse_command_sync(std::vector<std::string>::const_iterator iter, std::vector<std::string>::const_iterator end){
	parse_command_empty(iter, end);
}


void parse_command_module_control(std::vector<std::string>::const_iterator iter, std::vector<std::string>::const_iterator end, uint32_t &node_id, pilot::base::canopen::nmt_command_e &nmt_command){
	if(iter == end){
		throw std::logic_error("Missing option: node-id");
	}
	node_id = str_to_int(*iter);
	iter++;

	if(iter == end){
		throw std::logic_error("Missing option: nmt-command");
	}
	vnx::from_string_value(*iter, nmt_command);
	if(!nmt_command.is_valid()){
		throw std::logic_error("Unknown NMT commmand");
	}
	iter++;
}


void parse_command_heartbeat(std::vector<std::string>::const_iterator iter, std::vector<std::string>::const_iterator end, pilot::base::canopen::nmt_state_e &nmt_state){
	if(iter == end){
		throw std::logic_error("Missing option: nmt-state");
	}
	vnx::from_string_value(*iter, nmt_state);
	if(!nmt_state.is_valid()){
		throw std::logic_error("Unknown NMT state");
	}
	iter++;
}


std::vector<std::string>::const_iterator parse_command_address(std::vector<std::string>::const_iterator iter, std::vector<std::string>::const_iterator end, uint32_t &node_id, uint16_t &index, uint8_t &subindex){
	if(iter == end){
		throw std::logic_error("Missing option: node-id");
	}
	node_id = str_to_int(*iter);
	iter++;

	if(iter == end){
		throw std::logic_error("Missing option: index");
	}
	index = str_to_int(*iter);
	iter++;

	if(iter == end){
		throw std::logic_error("Missing option: subindex");
	}
	subindex = str_to_int(*iter);
	iter++;

	return iter;
}


void parse_segmented_data(std::vector<std::string>::const_iterator iter, std::vector<std::string>::const_iterator end, std::vector<uint8_t> &data){
	while(iter != end){
		data.emplace_back();
		data.back() = str_to_int(*iter);
		iter++;
	}
}





int main(int argc, char **argv){
	opmode_e opmode = opmode_e::NONE;
	int baud_rate;
	std::string device;
	uint32_t node_id;
	uint16_t index;
	uint8_t subindex;
	size_t size_expedited = 0;
	uint32_t data_expedited;
	std::vector<uint8_t> data_segmented;
	pilot::base::canopen::nmt_command_e nmt_command;
	pilot::base::canopen::nmt_state_e nmt_state;
	pilot::base::canopen::sdo_error_e sdo_error;

	std::vector<std::string> args;
	for(int i=0; i<argc; i++){
		args.push_back(argv[i]);
	}
	try{
		auto iter = parse_command(args, opmode, baud_rate, device);
		switch(opmode){
		case opmode_e::NONE: break;
		case opmode_e::SYNC: parse_command_sync(iter, args.end()); break;
		case opmode_e::MODULE_CONTROL: parse_command_module_control(iter, args.end(), node_id, nmt_command); break;
		case opmode_e::HEARTBEAT:
			if(iter == args.end()){
				throw std::logic_error("Missing option: node-id");
			}
			node_id = str_to_int(*iter);
			iter++;
			parse_command_heartbeat(iter, args.end(), nmt_state);
			break;
		case opmode_e::UPLOAD:
			iter = parse_command_address(iter, args.end(), node_id, index, subindex);
			parse_command_empty(iter, args.end());
			break;
		case opmode_e::DOWNLOAD:
			iter = parse_command_address(iter, args.end(), node_id, index, subindex);
			if(iter == args.end()){
				throw std::logic_error("No data size given for expedited download");
			}
			size_expedited = str_to_int(*iter);
			iter++;
			if(iter == args.end()){
				throw std::logic_error("No data given for expedited download");
			}
			data_expedited = str_to_int(*iter);
			iter++;
			parse_command_empty(iter, args.end());
			break;
		case opmode_e::DOWNLOAD_SEGMENTED:
			iter = parse_command_address(iter, args.end(), node_id, index, subindex);
			parse_segmented_data(iter, args.end(), data_segmented);
			break;
		case opmode_e::ABORT:
			iter = parse_command_address(iter, args.end(), node_id, index, subindex);
			if(iter == args.end()){
				throw std::logic_error("Missing option: sdo-error");
			}
			vnx::from_string_value(*iter, sdo_error);
			if(!sdo_error.is_valid()){
				throw std::logic_error("Unknown SDO error code");
			}
			iter++;
			parse_command_empty(iter, args.end());
		}
	}catch(const std::exception &err){
		std::cerr << "Argument error: " << err.what() << std::endl;
		std::cerr << std::endl;
		usage(args[0]);
		return 1;
	}

	if(opmode == opmode_e::NONE){
		std::cout << "No command given." << std::endl;
		usage(argv[0]);
		return 0;
	}

	pilot::base::canopen::node_t canopen_node;
	if(opmode == opmode_e::HEARTBEAT || opmode == opmode_e::UPLOAD || opmode == opmode_e::DOWNLOAD || opmode == opmode_e::DOWNLOAD_SEGMENTED || opmode == opmode_e::ABORT){
		canopen_node.id = node_id;
		try{
			canopen_node.calculate_can_ids();
		}catch(const std::exception &err){
			std::cerr << "CAN ID calculation failed with: " << err.what() << std::endl;
			return 1;
		}
	}

	std::shared_ptr<pilot::base::CAN_Interface> canctrl;
	try{
#ifdef _WIN32
		try{
			canctrl = std::make_shared<pilot::base::CAN_PeakUSB>(81, baud_rate, pilot::base::socketcan_options_t());
		}catch(const std::exception &err_peak){
			try{
				canctrl = std::make_shared<pilot::base::CAN_Kvaser>(0, baud_rate, pilot::base::socketcan_options_t());
			}catch(const std::exception &err_kvaser){
				throw std::runtime_error("PeakUSB: " + std::string(err_peak.what()) + "; Kvaser: " + std::string(err_kvaser.what()));
			}
		}
#else
		canctrl = std::make_shared<pilot::base::CAN_Socket>(device, pilot::base::socketcan_options_t());
#endif
	}catch(const std::exception &err){
		std::cerr << "Initialization error: " << err.what() << std::endl;
		return 1;
	}

	std::shared_ptr<const pilot::base::CAN_Frame> request;
	std::vector<std::shared_ptr<const pilot::base::CAN_Frame>> requests;
	if(opmode == opmode_e::SYNC){
		request = pilot::base::canopen::node_t::sync();
	}else if(opmode == opmode_e::MODULE_CONTROL){
		request = pilot::base::canopen::node_t::module_control(nmt_command, node_id);
	}else if(opmode == opmode_e::HEARTBEAT){
		request = canopen_node.heartbeat(nmt_state);
	}else if(opmode == opmode_e::UPLOAD){
		request = canopen_node.upload_request(index, subindex);
	}else if(opmode == opmode_e::DOWNLOAD){
		request = canopen_node.download_expedited(index, subindex, data_expedited, size_expedited);
	}else if(opmode == opmode_e::DOWNLOAD_SEGMENTED){
		requests = canopen_node.download_segmented(index, subindex, data_segmented);
	}else if(opmode == opmode_e::ABORT){
		request = canopen_node.abort_client(index, subindex, sdo_error);
	}

	try{
		if(request){
			canctrl->write(*request);
		}else if(!requests.empty()){
			canctrl->write(*requests.front());
		}
	}catch(const std::exception &err){
		std::cerr << "Write error: " << err.what() << std::endl;
		return 1;
	}

	if(opmode == opmode_e::UPLOAD || opmode == opmode_e::DOWNLOAD || opmode == opmode_e::DOWNLOAD_SEGMENTED){
		// in case we need them
		const auto upload_segment_request = canopen_node.upload_segment_request(index, subindex);
		bool toggle = true;
		size_t requests_seq = 1;

		while(true){
			pilot::base::CAN_Frame response;
			try{
				if(!canctrl->read(response, 200)){
					continue;
				}
			}catch(const std::exception &err){
				std::cerr << "Read error: " << err.what() << std::endl;
				return 1;
			}

			if(response.id == canopen_node.tx_sdo){
				const auto scs = canopen_node.get_sdo_scs(response);
				if(scs == pilot::base::canopen::sdo_scs_e::ABORT){
					const auto error = canopen_node.get_sdo_error(response);
					std::cerr << "SDO error: " << vnx::to_string_value(error) << std::endl;
				}else if(opmode == opmode_e::DOWNLOAD && scs == pilot::base::canopen::sdo_scs_e::INIT_DOWNLOAD_RESPONSE){
					const uint16_t index = response.data[1] | (response.data[2] << 8);
					const uint8_t subindex = response.data[3];
					std::cout << "Confirmed download to " << index << " / " << static_cast<unsigned int>(subindex) << std::endl;
					break;
				}else if(opmode == opmode_e::UPLOAD && scs == pilot::base::canopen::sdo_scs_e::INIT_UPLOAD_RESPONSE){
					const auto answer = canopen_node.get_uploaded_data(response);
					uint32_t data = 0;
					for(size_t i=0; i<answer.first.size(); i++){
						data |= (answer.first[i] << (8*i));
					}
					if(answer.second){
						if(answer.first.empty()){
							std::cout << "Data reserved for further use" << std::endl;
							break;
						}else{
							// expedited transfer, upload finished, data given
							std::cout << "Data of expedited upload: 0x" << std::hex << data << std::dec << std::endl;
							break;
						}
					}else{
						// segmented transfer, needs further commands, data size given
						std::cout << "Init of segmented upload, size is " << data << " bytes" << std::endl;
						auto frame = toggle ? upload_segment_request.first : upload_segment_request.second;
						try{
							canctrl->write(*frame);
						}catch(const std::exception &err){
							std::cerr << "Write error: " << err.what() << std::endl;
						}
						toggle = !toggle;
					}
				}else if(opmode == opmode_e::UPLOAD && scs == pilot::base::canopen::sdo_scs_e::SEGMENT_UPLOAD_RESPONSE){
					const auto answer = canopen_node.get_uploaded_data(response);
					std::cout << "Uploaded data: ";
					bool first_one = true;
					for(auto byte : answer.first){
						if(!first_one){
							std::cout << " ";
						}
						first_one = false;
						std::cout << "0x" << std::hex << static_cast<unsigned int>(byte) << std::dec;
					}
					std::cout << std::endl;
					if(answer.second){
						break;
					}else{
						auto frame = toggle ? upload_segment_request.first : upload_segment_request.second;
						try{
							canctrl->write(*frame);
						}catch(const std::exception &err){
							std::cerr << "Write error: " << err.what() << std::endl;
						}
						toggle = !toggle;
					}
				}else if(opmode == opmode_e::DOWNLOAD_SEGMENTED && (scs == pilot::base::canopen::sdo_scs_e::INIT_DOWNLOAD_RESPONSE || scs == pilot::base::canopen::sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE)){
					if(requests_seq < requests.size()){
						std::cout << "Sending next download segment (" << requests_seq << " / " << requests.size()-1 << ")" << std::endl;
						try{
							canctrl->write(*requests[requests_seq]);
						}catch(const std::exception &err){
							std::cerr << "Write error: " << err.what();
						}
						requests_seq++;
					}else{
						std::cout << "Segmented download finished" << std::endl;
					}
				}else{
					std::cerr << "Ignoring SCS " << vnx::to_string_value(scs) << std::endl;
				}
			}else if(response.id == canopen_node.emcy){
				const auto error = canopen_node.handle_emcy(response);
				std::cerr << "EMCY: " << vnx::to_string_value(error) << std::endl;
				std::cerr << "EMCY register: " << vnx::to_string(canopen_node.emcy_register) << std::endl;
			}else{
				std::cout << "Ignoring CAN ID 0x" << std::hex << response.id << std::dec << std::endl;
			}
		}
	}


	std::cout << "End" << std::endl;
	canctrl->close();

	return 0;
}

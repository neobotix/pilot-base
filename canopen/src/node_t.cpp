/*
 * node_t.cpp
 *
 *  Created on: Jun 21, 2023
 *      Author: jaw
 */

#include <pilot/base/canopen/node_t.hxx>


namespace pilot {
namespace base {
namespace canopen {


static uint8_t convert_nmt_state(const nmt_state_e &state){
	switch(state){
	case nmt_state_e::BOOT_UP: return 0;
	case nmt_state_e::STOPPED: return 4;
	case nmt_state_e::OPERATIONAL: return 5;
	case nmt_state_e::PRE_OPERATIONAL: return 0x7f;
	}
	throw std::logic_error("Unknown NMT state code: " + vnx::to_string_value(state));
}


static uint8_t convert_nmt_command(const nmt_command_e &command){
	switch(command){
	case nmt_command_e::GO_TO_OPERATIONAL: return 1;
	case nmt_command_e::GO_TO_STOPPED: return 2;
	case nmt_command_e::GO_TO_PRE_OPERATIONAL: return 0x80;
	case nmt_command_e::GO_TO_RESET_NODE: return 0x81;
	case nmt_command_e::GO_TO_RESET_COMMUNICATION: return 0x82;
	}
	throw std::logic_error("Unknown NMT command code: " + vnx::to_string_value(command));
}


// (error class, error code, additional code)
static std::tuple<uint8_t, uint8_t, uint16_t> convert_sdo_error(const sdo_error_e &error){
	switch(error){
	case sdo_error_e::NO_ERROR: throw std::logic_error("No error");
	case sdo_error_e::TOGGLE_BIT_ERROR: return std::make_tuple(5, 3, 0);
	case sdo_error_e::TIMEOUT: return std::make_tuple(5, 4, 0);
	case sdo_error_e::INVALID_COMMAND: return std::make_tuple(5, 4, 1);
	case sdo_error_e::INVALID_BLOCK_SIZE: return std::make_tuple(5, 4, 2);
	case sdo_error_e::INVALID_BLOCK_SEQUENCE_NUMBER: return std::make_tuple(5, 4, 3);
	case sdo_error_e::INVALID_BLOCK_CRC: return std::make_tuple(5, 4, 4);
	case sdo_error_e::OUT_OF_MEMORY: return std::make_tuple(5, 4, 5);
	case sdo_error_e::OBJECT_ACCESS_WRITE_ONLY: return std::make_tuple(6, 1, 1);
	case sdo_error_e::OBJECT_ACCESS_READ_ONLY: return std::make_tuple(6, 1, 2);
	case sdo_error_e::OBJECT_NON_EXISTENT: return std::make_tuple(6, 2, 0);
	case sdo_error_e::INDEX_RESERVED: return std::make_tuple(6, 4, 0);
	case sdo_error_e::CANNOT_MAP_TO_PDO: return std::make_tuple(6, 4, 0x41);
	case sdo_error_e::PDO_LENGTH_EXCEEDED: return std::make_tuple(6, 4, 0x42);
	case sdo_error_e::GENERAL_PARAMETER_INCOMPATIBILITY: return std::make_tuple(6, 4, 0x43);
	case sdo_error_e::GENERAL_INTERNAL_INCOMPATIBILITY: return std::make_tuple(6, 4, 0x44);        // or is it 0x47? Sources differ.
	case sdo_error_e::HARDWARE_FAULT: return std::make_tuple(6, 6, 0);
	case sdo_error_e::TYPE_CONFLICT: return std::make_tuple(6, 7, 0);
	case sdo_error_e::TYPE_MISMATCH: return std::make_tuple(6, 7, 0x10);
	case sdo_error_e::OBJECT_LENGTH_TOO_HIGH: return std::make_tuple(6, 7, 0x12);
	case sdo_error_e::OBJECT_LENGTH_TOO_LOW: return std::make_tuple(6, 7, 0x13);
	case sdo_error_e::OBJECT_ATTRIBUTE_INCONSISTENT: return std::make_tuple(6, 9, 0);
	case sdo_error_e::SUB_INDEX_DOES_NOT_EXIST: return std::make_tuple(6, 9, 0x11);
	case sdo_error_e::PARAMETER_VALUE_OUT_OF_RANGE: return std::make_tuple(6, 9, 0x30);
	case sdo_error_e::PARAMETER_VALUE_TOO_HIGH: return std::make_tuple(6, 9, 0x31);
	case sdo_error_e::PARAMETER_VALUE_TOO_LOW: return std::make_tuple(6, 9, 0x32);
	case sdo_error_e::SUB_PARAMETER_VALUE_OUT_OF_RANGE: return std::make_tuple(6, 9, 0x33);
	case sdo_error_e::MAX_VALUE_LESS_THAN_MIN_VALUE: return std::make_tuple(6, 9, 0x36);
	case sdo_error_e::CONNECTION_ERROR: return std::make_tuple(6, 10, 0x23);
	case sdo_error_e::DATA_TRANSFER: return std::make_tuple(8, 0, 0x20);
	case sdo_error_e::DATA_TRANSFER_LOCAL: return std::make_tuple(8, 0, 0x21);
	case sdo_error_e::DATA_TRANSFER_DEVICE_STATE: return std::make_tuple(8, 0, 0x22);
	case sdo_error_e::OBJECT_DICTIONARY_FAIL: return std::make_tuple(8, 0, 0x23);
	case sdo_error_e::NO_DATA: return std::make_tuple(8, 0, 0x24);
	case sdo_error_e::GENERAL_ERROR: return std::make_tuple(8, 0, 0);
	}
	throw std::logic_error("Unknown or unspecific SDO error code: " + vnx::to_string_value(error));
}


static void set_ccs(CAN_Frame &frame, const sdo_ccs_e &ccs){
	uint8_t ccs_byte;
	switch(ccs){
	case sdo_ccs_e::INIT_DOWNLOAD: ccs_byte = 1; break;
	case sdo_ccs_e::INIT_UPLOAD: ccs_byte = 2; break;
	case sdo_ccs_e::SEGMENT_DOWNLOAD: ccs_byte = 0; break;
	case sdo_ccs_e::SEGMENT_UPLOAD: ccs_byte = 3; break;
	case sdo_ccs_e::BLOCK_DOWNLOAD: ccs_byte = 6; break;
	case sdo_ccs_e::BLOCK_UPLOAD: ccs_byte = 5; break;
	case sdo_ccs_e::ABORT: ccs_byte = 4; break;
	default: throw std::logic_error("Unknown CCS " + vnx::to_string_value(ccs));
	}

	const uint8_t zero_mask = 0b00011111;
	frame.data[0] &= zero_mask;
	frame.data[0] |= (ccs_byte << 5);
}


static void set_scs(CAN_Frame &frame, const sdo_scs_e &scs){
	uint8_t scs_byte;
	switch(scs){
	case sdo_scs_e::INIT_DOWNLOAD_RESPONSE: scs_byte = 3; break;
	case sdo_scs_e::INIT_UPLOAD_RESPONSE: scs_byte = 2; break;
	case sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE: scs_byte = 1; break;
	case sdo_scs_e::SEGMENT_UPLOAD_RESPONSE: scs_byte = 0; break;
	case sdo_scs_e::BLOCK_DOWNLOAD: scs_byte = 6; break;
	case sdo_scs_e::BLOCK_UPLOAD: scs_byte = 5; break;
	case sdo_scs_e::ABORT: scs_byte = 4; break;
	default: throw std::logic_error("Unknown SCS " + vnx::to_string_value(scs));
	}

	const uint8_t zero_mask = 0b00011111;
	frame.data[0] &= zero_mask;
	frame.data[0] |= (scs_byte << 5);
}


static std::shared_ptr<CAN_Frame> transfer_expedited(uint16_t index, uint8_t subindex, uint32_t data, uint32_t num_bytes){
	if(num_bytes > 4){
		throw std::logic_error("Cannot transfer more than 4 bytes in expedited transfer");
	}
	const uint8_t no_data = (4 - num_bytes) << 2;
	const uint8_t expedited = 1 << 1;
	const uint8_t size_indicator = 1;

	auto frame = CAN_Frame::create();
	// Remember to set id and ccs/scs
	frame->size = 8;
	frame->data[0] |= no_data | expedited | size_indicator;
	frame->data[1] = index;
	frame->data[2] = (index >> 8);
	frame->data[3] = subindex;
	frame->data[4] = data;
	frame->data[5] = (data >> 8);
	frame->data[6] = (data >> 16);
	frame->data[7] = (data >> 24);
	return frame;
}


static std::vector<std::shared_ptr<CAN_Frame>> transfer_segmented(uint16_t index, uint8_t subindex, const std::vector<uint8_t> &data){
	std::vector<std::shared_ptr<CAN_Frame>> frames;

	{
		// first frame initiates the transfer
		const uint8_t size_indicator = 1;
		const uint32_t data_size = data.size();

		auto frame = CAN_Frame::create();
		// Remember to set id and ccs/scs
		frame->size = 8;
		frame->data[0] |= size_indicator;
		frame->data[1] = index;
		frame->data[2] = (index >> 8);
		frame->data[3] = subindex;
		frame->data[4] = data_size;
		frame->data[5] = (data_size >> 8);
		frame->data[6] = (data_size >> 16);
		frame->data[7] = (data_size >> 24);
		frames.push_back(frame);
	}

	// remaining frames continue the transfer
	size_t data_offset = 0;
	bool toggle_bit = false;
	while(data_offset < data.size()){
		const size_t max_bytes = 7;
		const size_t num_bytes = std::min(data.size() - data_offset, max_bytes);
		const uint8_t no_data = max_bytes - num_bytes;
		const bool is_last = (data_offset + num_bytes >= data.size());

		auto frame = CAN_Frame::create();
		// Remember to set id and ccs/scs
		frame->size = 8;
		frame->data[0] |= (toggle_bit << 4) | (no_data << 1) | is_last;
		for(size_t i=0; i<num_bytes; i++){
			frame->data[1+i] = data[data_offset+i];
		}
		frames.push_back(frame);

		data_offset += num_bytes;
		toggle_bit = !toggle_bit;
	}

	return frames;
}


static std::pair<std::vector<uint8_t>, bool> get_transferred_data_first_frame(const CAN_Frame &frame){
	const uint8_t no_data = (frame.data[0] >> 2) & 0b11;
	const bool is_expedited = (frame.data[0] >> 1) & 0b1;
	const bool size_indicator = frame.data[0] & 0b1;
	if(is_expedited){
		if(!size_indicator){
			throw std::runtime_error("Expedited transfer with no data size given");
		}
		const size_t num_bytes = 4 - no_data;
		std::vector<uint8_t> data;
		for(size_t i=0; i<num_bytes; i++){
			data.push_back(frame.data[4+i]);
		}
		return std::make_pair(data, true);
	}else{
		if(!size_indicator){
			throw std::runtime_error("Segmented transfer init with no data size given");
		}
		//const uint32_t data_length = frame.data[4] | (frame.data[5] << 8) | (frame.data[6] << 16) | (frame.data[7] << 24);
		std::vector<uint8_t> data;
		for(size_t i=0; i<4; i++){
			data.push_back(frame.data[4+i]);
		}
		return std::make_pair(data, false);
	}
}


static std::pair<std::vector<uint8_t>, bool> get_transferred_data_next_frame(const CAN_Frame &frame){
	//const bool toggle_bit = (frame.data[0] >> 4) & 0b1;
	const uint8_t no_data = (frame.data[0] >> 1) & 0b111;
	const bool is_last = frame.data[0] & 0b1;
	const size_t num_bytes = 7 - no_data;
	std::vector<uint8_t> data;
	for(size_t i=0; i<num_bytes; i++){
		data.push_back(frame.data[1+i]);
	}
	return std::make_pair(data, is_last);
}


static std::shared_ptr<CAN_Frame> abort_transfer(uint16_t index, uint8_t subindex, const sdo_error_e &error){
	const auto codes = convert_sdo_error(error);
	auto frame = CAN_Frame::create();
	// Remember to set id and ccs/scs
	frame->size = 8;
	frame->data[1] = index;
	frame->data[2] = (index >> 8);
	frame->data[3] = subindex;
	frame->data[4] = std::get<2>(codes);
	frame->data[5] = (std::get<2>(codes) >> 8);
	frame->data[6] = std::get<1>(codes);
	frame->data[7] = std::get<0>(codes);
	return frame;
}


std::shared_ptr<const CAN_Frame> node_t::sync(){
	auto frame = CAN_Frame::create();
	frame->id = 0x80;
	frame->size = 0;
	return frame;
}


std::shared_ptr<const CAN_Frame> node_t::module_control(const nmt_command_e &command, const uint8_t &node_id){
	const uint8_t command_byte = convert_nmt_command(command);

	auto frame = CAN_Frame::create();
	frame->id = 0;
	frame->size = 2;
	frame->data[0] = command_byte;
	frame->data[1] = node_id;
	return frame;
}


void node_t::calculate_can_ids(){
	if(use_predefined_connection_set){
		if(id <= 0){
			throw std::logic_error("Node ID must not be 0");
		}
		emcy = 0x80 + id;
		tx_pdo_1 = 0x180 + id;
		rx_pdo_1 = 0x200 + id;
		tx_pdo_2 = 0x280 + id;
		rx_pdo_2 = 0x300 + id;
		tx_pdo_3 = 0x380 + id;
		rx_pdo_3 = 0x400 + id;
		tx_pdo_4 = 0x480 + id;
		rx_pdo_4 = 0x500 + id;
		tx_sdo = 0x580 + id;
		rx_sdo = 0x600 + id;
		nmt = 0x700 + id;
	}
}


std::shared_ptr<const CAN_Frame> node_t::heartbeat(const nmt_state_e &state) const{
	const uint8_t state_byte = convert_nmt_state(state);

	auto frame = CAN_Frame::create();
	frame->id = nmt;
	frame->size = 1;
	frame->data[0] = state_byte;
	return frame;
}


emcy_code_e node_t::handle_emcy(const CAN_Frame &frame){
	if(frame.id != emcy){
		throw std::logic_error("CAN frame ID " + std::to_string(frame.id) + " is not node EMCY id " + std::to_string(emcy));
	}
	const uint16_t error_code = frame.get_int(0, 16);
	const uint8_t error_register_mask = frame.get_int(16, 8);

	emcy_code_e err = emcy_code_e::NO_ERROR;
	switch(error_code & 0xff00){
	case 0x1000: err = emcy_code_e::GENERIC_ERROR; break;
	case 0x2000: err = emcy_code_e::CURRENT; break;
	case 0x2100: err = emcy_code_e::CURRENT_INPUT; break;
	case 0x2200: err = emcy_code_e::CURRENT_INSIDE; break;
	case 0x2300: err = emcy_code_e::CURRENT_OUTPUT; break;
	case 0x3000: err = emcy_code_e::VOLTAGE; break;
	case 0x3100: err = emcy_code_e::VOLTAGE_MAINS; break;
	case 0x3200: err = emcy_code_e::VOLTAGE_INSIDE; break;
	case 0x3300: err = emcy_code_e::VOLTAGE_OUTPUT; break;
	case 0x4000: err = emcy_code_e::TEMPERATURE; break;
	case 0x4100: err = emcy_code_e::TEMPERATURE_AMBIENT; break;
	case 0x4200: err = emcy_code_e::TEMPERATURE_DEVICE; break;
	case 0x5000: err = emcy_code_e::HARDWARE; break;
	case 0x6000: err = emcy_code_e::SOFTWARE; break;
	case 0x6100: err = emcy_code_e::INTERNAL_SOFTWARE; break;
	case 0x6200: err = emcy_code_e::USER_SOFTWARE; break;
	case 0x6300: err = emcy_code_e::DATA_SET; break;
	case 0x7000: err = emcy_code_e::ADDITIONAL_MODULES; break;
	case 0x8000: err = emcy_code_e::MONITORING; break;
	case 0x8100:
		err = emcy_code_e::COMMUNICATION;
		if(error_code == 0x8110){
			err = emcy_code_e::CAN_OVERRUN;
		}else if(error_code == 0x8120){
			err = emcy_code_e::CAN_ERROR_PASSIVE;
		}else if(error_code == 0x8130){
			err = emcy_code_e::HEARTBEAT_ERROR;
		}else if(error_code == 0x8140){
			err = emcy_code_e::CAN_RECOVERED;
		}else if(error_code == 0x8150){
			err = emcy_code_e::CAN_ID_COLLISION;
		}
		break;
	case 0x8200:
		err = emcy_code_e::PROTOCOL_ERROR;
		if(error_code == 0x8210){
			err = emcy_code_e::PDO_LENGTH_ERROR;
		}else if(error_code == 0x8220){
			err = emcy_code_e::PDO_LENGTH_EXCEEDED;
		}else if(error_code == 0x8230){
			err = emcy_code_e::DAM_MPDO_NOT_PROCESSED;
		}else if(error_code == 0x8240){
			err = emcy_code_e::UNEXPECTED_SYNC_LENGTH;
		}else if(error_code == 0x8250){
			err = emcy_code_e::RPDO_TIMEOUT;
		}
		break;
	case 0x9000: err = emcy_code_e::EXTERNAL_ERROR; break;
	case 0xf000: err = emcy_code_e::ADDITIONAL_FUNCTIONS; break;
	case 0xff00: err = emcy_code_e::DEVICE_SPECIFIC; break;
	}

	emcy_register.clear();
	if(error_register_mask & 1)   emcy_register.insert(emcy_register_e::GENERIC);
	if(error_register_mask & 2)   emcy_register.insert(emcy_register_e::CURRENT);
	if(error_register_mask & 4)   emcy_register.insert(emcy_register_e::VOLTAGE);
	if(error_register_mask & 8)   emcy_register.insert(emcy_register_e::TEMPERATURE);
	if(error_register_mask & 16)  emcy_register.insert(emcy_register_e::COMMUNICATION);
	if(error_register_mask & 32)  emcy_register.insert(emcy_register_e::DEVICE_PROFILE_SPECIFIC);
	if(error_register_mask & 128) emcy_register.insert(emcy_register_e::MANUFACTURER_SPECIFIC);

	return err;
}


sdo_scs_e node_t::get_sdo_scs(const CAN_Frame &frame) const{
	if(frame.id != tx_sdo){
		throw std::logic_error("CAN frame ID " + std::to_string(frame.id) + " is not node SDO-Tx id " + std::to_string(tx_sdo));
	}

	const uint8_t scs = (frame.data[0] >> 5);
	switch(scs){
	case 0: return sdo_scs_e::SEGMENT_UPLOAD_RESPONSE;
	case 1: return sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE;
	case 2: return sdo_scs_e::INIT_UPLOAD_RESPONSE;
	case 3: return sdo_scs_e::INIT_DOWNLOAD_RESPONSE;
	case 4: return sdo_scs_e::ABORT;
	case 5: return sdo_scs_e::BLOCK_UPLOAD;
	case 6: return sdo_scs_e::BLOCK_DOWNLOAD;
	}
	throw std::logic_error("Invalid SCS value: " + std::to_string(static_cast<int>(scs)));
}


sdo_ccs_e node_t::get_sdo_ccs(const CAN_Frame &frame) const{
	if(frame.id != rx_sdo){
		throw std::logic_error("CAN frame ID " + std::to_string(frame.id) + " is not node SDO-Rx id " + std::to_string(rx_sdo));
	}

	const uint8_t ccs = (frame.data[0] >> 5);
	switch(ccs){
	case 0: return sdo_ccs_e::SEGMENT_DOWNLOAD;
	case 1: return sdo_ccs_e::INIT_DOWNLOAD;
	case 2: return sdo_ccs_e::INIT_UPLOAD;
	case 3: return sdo_ccs_e::SEGMENT_UPLOAD;
	case 4: return sdo_ccs_e::ABORT;
	case 5: return sdo_ccs_e::BLOCK_UPLOAD;
	case 6: return sdo_ccs_e::BLOCK_DOWNLOAD;
	}
	throw std::logic_error("Invalid CCS value: " + std::to_string(static_cast<int>(ccs)));
}


sdo_error_e node_t::get_sdo_error(const CAN_Frame &frame) const{
	if(frame.id == tx_sdo){
		if(get_sdo_scs(frame) != sdo_scs_e::ABORT){
			return sdo_error_e::NO_ERROR;
		}
	}else if(frame.id == rx_sdo){
		if(get_sdo_ccs(frame) != sdo_ccs_e::ABORT){
			return sdo_error_e::NO_ERROR;
		}
	}else{
		throw std::logic_error("CAN frame ID " + std::to_string(frame.id) + " is neither SDO-Rx id nor SDO-Tx id of node");
	}

	const uint8_t error_class = frame.data[7];
	const uint8_t error_code = frame.data[6];
	const uint16_t additional_code = frame.data[4] | (frame.data[5] << 8);
	switch(error_class){
	case 5:
		switch(error_code){
		case 3:
			switch(additional_code){
			case 0: return sdo_error_e::TOGGLE_BIT_ERROR;
			}
			return sdo_error_e::PARAMETER_INCONSISTENT;
		case 4:
			switch(additional_code){
			case 0: return sdo_error_e::TIMEOUT;
			case 1: return sdo_error_e::INVALID_COMMAND;
			case 2: return sdo_error_e::INVALID_BLOCK_SIZE;
			case 3: return sdo_error_e::INVALID_BLOCK_SEQUENCE_NUMBER;
			case 4: return sdo_error_e::INVALID_BLOCK_CRC;
			case 5: return sdo_error_e::OUT_OF_MEMORY;
			}
			return sdo_error_e::ILLEGAL_PARAMETER;
		}
		return sdo_error_e::SERVICE_ERROR;
	case 6:
		switch(error_code){
		case 1:
			switch(additional_code){
			case 1: return sdo_error_e::OBJECT_ACCESS_WRITE_ONLY;
			case 2: return sdo_error_e::OBJECT_ACCESS_READ_ONLY;
			}
			return sdo_error_e::OBJECT_ACCESS_UNSUPPORTED;
		case 2: return sdo_error_e::OBJECT_NON_EXISTENT;
		case 4:
			switch(additional_code){
			case 0: return sdo_error_e::INDEX_RESERVED;
			case 0x41: return sdo_error_e::CANNOT_MAP_TO_PDO;
			case 0x42: return sdo_error_e::PDO_LENGTH_EXCEEDED;
			case 0x43: return sdo_error_e::GENERAL_PARAMETER_INCOMPATIBILITY;
			case 0x44:
			case 0x47: return sdo_error_e::GENERAL_INTERNAL_INCOMPATIBILITY;
			}
			return sdo_error_e::INVALID_ADDRESS;
		case 6: return sdo_error_e::HARDWARE_FAULT;
		case 7:
			switch(additional_code){
			case 0x10: return sdo_error_e::TYPE_MISMATCH;
			case 0x12: return sdo_error_e::OBJECT_LENGTH_TOO_HIGH;
			case 0x13: return sdo_error_e::OBJECT_LENGTH_TOO_LOW;
			}
			return sdo_error_e::TYPE_CONFLICT;
		case 9:
			switch(additional_code){
			case 0x11: return sdo_error_e::SUB_INDEX_DOES_NOT_EXIST;
			case 0x30: return sdo_error_e::PARAMETER_VALUE_OUT_OF_RANGE;
			case 0x31: return sdo_error_e::PARAMETER_VALUE_TOO_HIGH;
			case 0x32: return sdo_error_e::PARAMETER_VALUE_TOO_LOW;
			case 0x33: return sdo_error_e::SUB_PARAMETER_VALUE_OUT_OF_RANGE;
			case 0x36: return sdo_error_e::MAX_VALUE_LESS_THAN_MIN_VALUE;
			}
			return sdo_error_e::OBJECT_ATTRIBUTE_INCONSISTENT;
		case 10:
			return sdo_error_e::CONNECTION_ERROR;
		}
		return sdo_error_e::ACCESS_ERROR;
	case 8:
		switch(error_code){
		case 0:
			switch(additional_code){
			case 0x20: return sdo_error_e::DATA_TRANSFER;
			case 0x21: return sdo_error_e::DATA_TRANSFER_LOCAL;
			case 0x22: return sdo_error_e::DATA_TRANSFER_DEVICE_STATE;
			case 0x23: return sdo_error_e::OBJECT_DICTIONARY_FAIL;
			case 0x24: return sdo_error_e::NO_DATA;
			}
		}
		return sdo_error_e::GENERAL_ERROR;
	default:
		return sdo_error_e::GENERAL_ERROR;
	}
}


std::shared_ptr<const CAN_Frame> node_t::download_expedited(const uint16_t &index, const uint8_t &subindex, const uint32_t &data, const uint32_t &num_bytes) const{
	auto frame = transfer_expedited(index, subindex, data, num_bytes);
	frame->id = rx_sdo;
	set_ccs(*frame, sdo_ccs_e::INIT_DOWNLOAD);
	return frame;
}


std::shared_ptr<const CAN_Frame> node_t::upload_expedited(const uint16_t &index, const uint8_t &subindex, const uint32_t &data, const uint32_t &num_bytes) const{
	auto frame = transfer_expedited(index, subindex, data, num_bytes);
	frame->id = tx_sdo;
	set_scs(*frame, sdo_scs_e::INIT_UPLOAD_RESPONSE);
	return frame;
}


std::vector<std::shared_ptr<const CAN_Frame>> node_t::download_segmented(const uint16_t &index, const uint8_t &subindex, const std::vector<uint8_t> &data) const{
	auto frames = transfer_segmented(index, subindex, data);

	std::vector<std::shared_ptr<const CAN_Frame>> result;
	bool after_first = false;
	for(auto frame : frames){
		frame->id = rx_sdo;
		if(after_first){
			set_ccs(*frame, sdo_ccs_e::SEGMENT_DOWNLOAD);
		}else{
			set_ccs(*frame, sdo_ccs_e::INIT_DOWNLOAD);
		}
		after_first = true;
		result.push_back(frame);
	}
	return result;
}


std::vector<std::shared_ptr<const CAN_Frame>> node_t::upload_segmented(const uint16_t &index, const uint8_t &subindex, const std::vector<uint8_t> &data) const{
	auto frames = transfer_segmented(index, subindex, data);

	std::vector<std::shared_ptr<const CAN_Frame>> result;
	bool after_first = false;
	for(auto frame : frames){
		frame->id = tx_sdo;
		if(after_first){
			set_scs(*frame, sdo_scs_e::SEGMENT_UPLOAD_RESPONSE);
		}else{
			set_scs(*frame, sdo_scs_e::INIT_UPLOAD_RESPONSE);
		}
		after_first = true;
		result.push_back(frame);
	}
	return result;
}


std::shared_ptr<const CAN_Frame> node_t::upload_request(const uint16_t &index, const uint8_t &subindex) const{
	auto frame = CAN_Frame::create();
	frame->id = rx_sdo;
	frame->size = 8;
	set_ccs(*frame, sdo_ccs_e::INIT_UPLOAD);
	frame->data[1] = index;
	frame->data[2] = (index >> 8);
	frame->data[3] = subindex;
	return frame;
}


std::shared_ptr<const CAN_Frame> node_t::download_confirm(const uint16_t &index, const uint8_t &subindex) const{
	auto frame = CAN_Frame::create();
	frame->id = tx_sdo;
	frame->size = 8;
	set_scs(*frame, sdo_scs_e::INIT_DOWNLOAD_RESPONSE);
	frame->data[1] = index;
	frame->data[2] = (index >> 8);
	frame->data[3] = subindex;
	return frame;
}


std::pair<std::shared_ptr<const CAN_Frame>, std::shared_ptr<const CAN_Frame>> node_t::upload_segment_request(const uint16_t &index, const uint8_t &subindex) const{
	auto frame_1 = CAN_Frame::create();
	frame_1->id = rx_sdo;
	frame_1->size = 8;
	set_ccs(*frame_1, sdo_ccs_e::SEGMENT_UPLOAD);
	frame_1->data[1] = index;
	frame_1->data[2] = (index >> 8);
	frame_1->data[3] = subindex;

	auto frame_2 = vnx::clone(frame_1);
	frame_2->data[0] |= (1 << 4);

	return std::make_pair(frame_1, frame_2);
}


std::pair<std::shared_ptr<const CAN_Frame>, std::shared_ptr<const CAN_Frame>> node_t::download_segment_request(const uint16_t &index, const uint8_t &subindex) const{
	auto frame_1 = CAN_Frame::create();
	frame_1->id = tx_sdo;
	frame_1->size = 8;
	set_scs(*frame_1, sdo_scs_e::SEGMENT_DOWNLOAD_RESPONSE);
	frame_1->data[1] = index;
	frame_1->data[2] = (index >> 8);
	frame_1->data[3] = subindex;

	auto frame_2 = vnx::clone(frame_1);
	frame_2->data[0] |= (1 << 4);

	return std::make_pair(frame_1, frame_2);
}


std::pair<std::vector<uint8_t>, bool> node_t::get_uploaded_data(const CAN_Frame &frame) const{
	const auto scs = get_sdo_scs(frame);
	if(scs != sdo_scs_e::INIT_UPLOAD_RESPONSE && scs != sdo_scs_e::SEGMENT_UPLOAD_RESPONSE){
		throw std::logic_error("Frame is not an upload response: " + vnx::to_string_value(scs));
	}

	if(scs == sdo_scs_e::INIT_UPLOAD_RESPONSE){
		return get_transferred_data_first_frame(frame);
	}else if(scs == sdo_scs_e::SEGMENT_UPLOAD_RESPONSE){
		return get_transferred_data_next_frame(frame);
	}

	// -Wreturn-type
	throw std::runtime_error("Unreachable");
}


std::pair<std::vector<uint8_t>, bool> node_t::get_downloaded_data(const CAN_Frame &frame) const{
	const auto ccs = get_sdo_ccs(frame);
	if(ccs != sdo_ccs_e::INIT_DOWNLOAD && ccs != sdo_ccs_e::SEGMENT_DOWNLOAD){
		throw std::logic_error("Frame is not a download command: " + vnx::to_string_value(ccs));
	}

	if(ccs == sdo_ccs_e::INIT_DOWNLOAD){
		return get_transferred_data_first_frame(frame);
	}else if(ccs == sdo_ccs_e::SEGMENT_DOWNLOAD){
		return get_transferred_data_next_frame(frame);
	}

	// -Wreturn-type
	throw std::runtime_error("Unreachable");
}


std::shared_ptr<const CAN_Frame> node_t::abort_server(const uint16_t &index, const uint8_t &subindex, const sdo_error_e &error) const{
	auto frame = abort_transfer(index, subindex, error);
	frame->id = tx_sdo;
	set_scs(*frame, sdo_scs_e::ABORT);
	return frame;
}


std::shared_ptr<const CAN_Frame> node_t::abort_client(const uint16_t &index, const uint8_t &subindex, const sdo_error_e &error) const{
	auto frame = abort_transfer(index, subindex, error);
	frame->id = rx_sdo;
	set_ccs(*frame, sdo_ccs_e::ABORT);
	return frame;
}


} // canopen
} // base
} // pilot



// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/canopen/package.hxx>
#include <pilot/base/canopen/sdo_error_e.hxx>

#include <vnx/vnx.h>


namespace pilot {
namespace base {
namespace canopen {


const vnx::Hash64 sdo_error_e::VNX_TYPE_HASH(0x9b27dfeddc64e9c2ull);
const vnx::Hash64 sdo_error_e::VNX_CODE_HASH(0x20f19aa211c94138ull);

vnx::Hash64 sdo_error_e::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string sdo_error_e::get_type_name() const {
	return "pilot.base.canopen.sdo_error_e";
}

const vnx::TypeCode* sdo_error_e::get_type_code() const {
	return pilot::base::canopen::vnx_native_type_code_sdo_error_e;
}

std::shared_ptr<sdo_error_e> sdo_error_e::create() {
	return std::make_shared<sdo_error_e>();
}

std::shared_ptr<sdo_error_e> sdo_error_e::clone() const {
	return std::make_shared<sdo_error_e>(*this);
}

void sdo_error_e::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void sdo_error_e::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

vnx::bool_t sdo_error_e::is_valid() const {
	switch(value) {
		case ACCESS_ERROR: return true;
		case CANNOT_MAP_TO_PDO: return true;
		case CONNECTION_ERROR: return true;
		case DATA_TRANSFER: return true;
		case DATA_TRANSFER_DEVICE_STATE: return true;
		case DATA_TRANSFER_LOCAL: return true;
		case GENERAL_ERROR: return true;
		case GENERAL_INTERNAL_INCOMPATIBILITY: return true;
		case GENERAL_PARAMETER_INCOMPATIBILITY: return true;
		case HARDWARE_FAULT: return true;
		case ILLEGAL_PARAMETER: return true;
		case INDEX_RESERVED: return true;
		case INVALID_ADDRESS: return true;
		case INVALID_BLOCK_CRC: return true;
		case INVALID_BLOCK_SEQUENCE_NUMBER: return true;
		case INVALID_BLOCK_SIZE: return true;
		case INVALID_COMMAND: return true;
		case MAX_VALUE_LESS_THAN_MIN_VALUE: return true;
		case NO_DATA: return true;
		case NO_ERROR: return true;
		case OBJECT_ACCESS_READ_ONLY: return true;
		case OBJECT_ACCESS_UNSUPPORTED: return true;
		case OBJECT_ACCESS_WRITE_ONLY: return true;
		case OBJECT_ATTRIBUTE_INCONSISTENT: return true;
		case OBJECT_DICTIONARY_FAIL: return true;
		case OBJECT_LENGTH_TOO_HIGH: return true;
		case OBJECT_LENGTH_TOO_LOW: return true;
		case OBJECT_NON_EXISTENT: return true;
		case OUT_OF_MEMORY: return true;
		case PARAMETER_INCONSISTENT: return true;
		case PARAMETER_VALUE_OUT_OF_RANGE: return true;
		case PARAMETER_VALUE_TOO_HIGH: return true;
		case PARAMETER_VALUE_TOO_LOW: return true;
		case PDO_LENGTH_EXCEEDED: return true;
		case SERVICE_ERROR: return true;
		case SUB_INDEX_DOES_NOT_EXIST: return true;
		case SUB_PARAMETER_VALUE_OUT_OF_RANGE: return true;
		case TIMEOUT: return true;
		case TOGGLE_BIT_ERROR: return true;
		case TYPE_CONFLICT: return true;
		case TYPE_MISMATCH: return true;
	}
	return false;
}

std::string sdo_error_e::to_string() const {
	switch(value) {
		case ACCESS_ERROR: return "\"ACCESS_ERROR\"";
		case CANNOT_MAP_TO_PDO: return "\"CANNOT_MAP_TO_PDO\"";
		case CONNECTION_ERROR: return "\"CONNECTION_ERROR\"";
		case DATA_TRANSFER: return "\"DATA_TRANSFER\"";
		case DATA_TRANSFER_DEVICE_STATE: return "\"DATA_TRANSFER_DEVICE_STATE\"";
		case DATA_TRANSFER_LOCAL: return "\"DATA_TRANSFER_LOCAL\"";
		case GENERAL_ERROR: return "\"GENERAL_ERROR\"";
		case GENERAL_INTERNAL_INCOMPATIBILITY: return "\"GENERAL_INTERNAL_INCOMPATIBILITY\"";
		case GENERAL_PARAMETER_INCOMPATIBILITY: return "\"GENERAL_PARAMETER_INCOMPATIBILITY\"";
		case HARDWARE_FAULT: return "\"HARDWARE_FAULT\"";
		case ILLEGAL_PARAMETER: return "\"ILLEGAL_PARAMETER\"";
		case INDEX_RESERVED: return "\"INDEX_RESERVED\"";
		case INVALID_ADDRESS: return "\"INVALID_ADDRESS\"";
		case INVALID_BLOCK_CRC: return "\"INVALID_BLOCK_CRC\"";
		case INVALID_BLOCK_SEQUENCE_NUMBER: return "\"INVALID_BLOCK_SEQUENCE_NUMBER\"";
		case INVALID_BLOCK_SIZE: return "\"INVALID_BLOCK_SIZE\"";
		case INVALID_COMMAND: return "\"INVALID_COMMAND\"";
		case MAX_VALUE_LESS_THAN_MIN_VALUE: return "\"MAX_VALUE_LESS_THAN_MIN_VALUE\"";
		case NO_DATA: return "\"NO_DATA\"";
		case NO_ERROR: return "\"NO_ERROR\"";
		case OBJECT_ACCESS_READ_ONLY: return "\"OBJECT_ACCESS_READ_ONLY\"";
		case OBJECT_ACCESS_UNSUPPORTED: return "\"OBJECT_ACCESS_UNSUPPORTED\"";
		case OBJECT_ACCESS_WRITE_ONLY: return "\"OBJECT_ACCESS_WRITE_ONLY\"";
		case OBJECT_ATTRIBUTE_INCONSISTENT: return "\"OBJECT_ATTRIBUTE_INCONSISTENT\"";
		case OBJECT_DICTIONARY_FAIL: return "\"OBJECT_DICTIONARY_FAIL\"";
		case OBJECT_LENGTH_TOO_HIGH: return "\"OBJECT_LENGTH_TOO_HIGH\"";
		case OBJECT_LENGTH_TOO_LOW: return "\"OBJECT_LENGTH_TOO_LOW\"";
		case OBJECT_NON_EXISTENT: return "\"OBJECT_NON_EXISTENT\"";
		case OUT_OF_MEMORY: return "\"OUT_OF_MEMORY\"";
		case PARAMETER_INCONSISTENT: return "\"PARAMETER_INCONSISTENT\"";
		case PARAMETER_VALUE_OUT_OF_RANGE: return "\"PARAMETER_VALUE_OUT_OF_RANGE\"";
		case PARAMETER_VALUE_TOO_HIGH: return "\"PARAMETER_VALUE_TOO_HIGH\"";
		case PARAMETER_VALUE_TOO_LOW: return "\"PARAMETER_VALUE_TOO_LOW\"";
		case PDO_LENGTH_EXCEEDED: return "\"PDO_LENGTH_EXCEEDED\"";
		case SERVICE_ERROR: return "\"SERVICE_ERROR\"";
		case SUB_INDEX_DOES_NOT_EXIST: return "\"SUB_INDEX_DOES_NOT_EXIST\"";
		case SUB_PARAMETER_VALUE_OUT_OF_RANGE: return "\"SUB_PARAMETER_VALUE_OUT_OF_RANGE\"";
		case TIMEOUT: return "\"TIMEOUT\"";
		case TOGGLE_BIT_ERROR: return "\"TOGGLE_BIT_ERROR\"";
		case TYPE_CONFLICT: return "\"TYPE_CONFLICT\"";
		case TYPE_MISMATCH: return "\"TYPE_MISMATCH\"";
	}
	return std::to_string(value);
}

std::string sdo_error_e::to_string_value() const {
	switch(value) {
		case ACCESS_ERROR: return "ACCESS_ERROR";
		case CANNOT_MAP_TO_PDO: return "CANNOT_MAP_TO_PDO";
		case CONNECTION_ERROR: return "CONNECTION_ERROR";
		case DATA_TRANSFER: return "DATA_TRANSFER";
		case DATA_TRANSFER_DEVICE_STATE: return "DATA_TRANSFER_DEVICE_STATE";
		case DATA_TRANSFER_LOCAL: return "DATA_TRANSFER_LOCAL";
		case GENERAL_ERROR: return "GENERAL_ERROR";
		case GENERAL_INTERNAL_INCOMPATIBILITY: return "GENERAL_INTERNAL_INCOMPATIBILITY";
		case GENERAL_PARAMETER_INCOMPATIBILITY: return "GENERAL_PARAMETER_INCOMPATIBILITY";
		case HARDWARE_FAULT: return "HARDWARE_FAULT";
		case ILLEGAL_PARAMETER: return "ILLEGAL_PARAMETER";
		case INDEX_RESERVED: return "INDEX_RESERVED";
		case INVALID_ADDRESS: return "INVALID_ADDRESS";
		case INVALID_BLOCK_CRC: return "INVALID_BLOCK_CRC";
		case INVALID_BLOCK_SEQUENCE_NUMBER: return "INVALID_BLOCK_SEQUENCE_NUMBER";
		case INVALID_BLOCK_SIZE: return "INVALID_BLOCK_SIZE";
		case INVALID_COMMAND: return "INVALID_COMMAND";
		case MAX_VALUE_LESS_THAN_MIN_VALUE: return "MAX_VALUE_LESS_THAN_MIN_VALUE";
		case NO_DATA: return "NO_DATA";
		case NO_ERROR: return "NO_ERROR";
		case OBJECT_ACCESS_READ_ONLY: return "OBJECT_ACCESS_READ_ONLY";
		case OBJECT_ACCESS_UNSUPPORTED: return "OBJECT_ACCESS_UNSUPPORTED";
		case OBJECT_ACCESS_WRITE_ONLY: return "OBJECT_ACCESS_WRITE_ONLY";
		case OBJECT_ATTRIBUTE_INCONSISTENT: return "OBJECT_ATTRIBUTE_INCONSISTENT";
		case OBJECT_DICTIONARY_FAIL: return "OBJECT_DICTIONARY_FAIL";
		case OBJECT_LENGTH_TOO_HIGH: return "OBJECT_LENGTH_TOO_HIGH";
		case OBJECT_LENGTH_TOO_LOW: return "OBJECT_LENGTH_TOO_LOW";
		case OBJECT_NON_EXISTENT: return "OBJECT_NON_EXISTENT";
		case OUT_OF_MEMORY: return "OUT_OF_MEMORY";
		case PARAMETER_INCONSISTENT: return "PARAMETER_INCONSISTENT";
		case PARAMETER_VALUE_OUT_OF_RANGE: return "PARAMETER_VALUE_OUT_OF_RANGE";
		case PARAMETER_VALUE_TOO_HIGH: return "PARAMETER_VALUE_TOO_HIGH";
		case PARAMETER_VALUE_TOO_LOW: return "PARAMETER_VALUE_TOO_LOW";
		case PDO_LENGTH_EXCEEDED: return "PDO_LENGTH_EXCEEDED";
		case SERVICE_ERROR: return "SERVICE_ERROR";
		case SUB_INDEX_DOES_NOT_EXIST: return "SUB_INDEX_DOES_NOT_EXIST";
		case SUB_PARAMETER_VALUE_OUT_OF_RANGE: return "SUB_PARAMETER_VALUE_OUT_OF_RANGE";
		case TIMEOUT: return "TIMEOUT";
		case TOGGLE_BIT_ERROR: return "TOGGLE_BIT_ERROR";
		case TYPE_CONFLICT: return "TYPE_CONFLICT";
		case TYPE_MISMATCH: return "TYPE_MISMATCH";
	}
	return std::to_string(value);
}

std::string sdo_error_e::to_string_value_full() const {
	switch(value) {
		case ACCESS_ERROR: return "pilot.base.canopen.sdo_error_e.ACCESS_ERROR";
		case CANNOT_MAP_TO_PDO: return "pilot.base.canopen.sdo_error_e.CANNOT_MAP_TO_PDO";
		case CONNECTION_ERROR: return "pilot.base.canopen.sdo_error_e.CONNECTION_ERROR";
		case DATA_TRANSFER: return "pilot.base.canopen.sdo_error_e.DATA_TRANSFER";
		case DATA_TRANSFER_DEVICE_STATE: return "pilot.base.canopen.sdo_error_e.DATA_TRANSFER_DEVICE_STATE";
		case DATA_TRANSFER_LOCAL: return "pilot.base.canopen.sdo_error_e.DATA_TRANSFER_LOCAL";
		case GENERAL_ERROR: return "pilot.base.canopen.sdo_error_e.GENERAL_ERROR";
		case GENERAL_INTERNAL_INCOMPATIBILITY: return "pilot.base.canopen.sdo_error_e.GENERAL_INTERNAL_INCOMPATIBILITY";
		case GENERAL_PARAMETER_INCOMPATIBILITY: return "pilot.base.canopen.sdo_error_e.GENERAL_PARAMETER_INCOMPATIBILITY";
		case HARDWARE_FAULT: return "pilot.base.canopen.sdo_error_e.HARDWARE_FAULT";
		case ILLEGAL_PARAMETER: return "pilot.base.canopen.sdo_error_e.ILLEGAL_PARAMETER";
		case INDEX_RESERVED: return "pilot.base.canopen.sdo_error_e.INDEX_RESERVED";
		case INVALID_ADDRESS: return "pilot.base.canopen.sdo_error_e.INVALID_ADDRESS";
		case INVALID_BLOCK_CRC: return "pilot.base.canopen.sdo_error_e.INVALID_BLOCK_CRC";
		case INVALID_BLOCK_SEQUENCE_NUMBER: return "pilot.base.canopen.sdo_error_e.INVALID_BLOCK_SEQUENCE_NUMBER";
		case INVALID_BLOCK_SIZE: return "pilot.base.canopen.sdo_error_e.INVALID_BLOCK_SIZE";
		case INVALID_COMMAND: return "pilot.base.canopen.sdo_error_e.INVALID_COMMAND";
		case MAX_VALUE_LESS_THAN_MIN_VALUE: return "pilot.base.canopen.sdo_error_e.MAX_VALUE_LESS_THAN_MIN_VALUE";
		case NO_DATA: return "pilot.base.canopen.sdo_error_e.NO_DATA";
		case NO_ERROR: return "pilot.base.canopen.sdo_error_e.NO_ERROR";
		case OBJECT_ACCESS_READ_ONLY: return "pilot.base.canopen.sdo_error_e.OBJECT_ACCESS_READ_ONLY";
		case OBJECT_ACCESS_UNSUPPORTED: return "pilot.base.canopen.sdo_error_e.OBJECT_ACCESS_UNSUPPORTED";
		case OBJECT_ACCESS_WRITE_ONLY: return "pilot.base.canopen.sdo_error_e.OBJECT_ACCESS_WRITE_ONLY";
		case OBJECT_ATTRIBUTE_INCONSISTENT: return "pilot.base.canopen.sdo_error_e.OBJECT_ATTRIBUTE_INCONSISTENT";
		case OBJECT_DICTIONARY_FAIL: return "pilot.base.canopen.sdo_error_e.OBJECT_DICTIONARY_FAIL";
		case OBJECT_LENGTH_TOO_HIGH: return "pilot.base.canopen.sdo_error_e.OBJECT_LENGTH_TOO_HIGH";
		case OBJECT_LENGTH_TOO_LOW: return "pilot.base.canopen.sdo_error_e.OBJECT_LENGTH_TOO_LOW";
		case OBJECT_NON_EXISTENT: return "pilot.base.canopen.sdo_error_e.OBJECT_NON_EXISTENT";
		case OUT_OF_MEMORY: return "pilot.base.canopen.sdo_error_e.OUT_OF_MEMORY";
		case PARAMETER_INCONSISTENT: return "pilot.base.canopen.sdo_error_e.PARAMETER_INCONSISTENT";
		case PARAMETER_VALUE_OUT_OF_RANGE: return "pilot.base.canopen.sdo_error_e.PARAMETER_VALUE_OUT_OF_RANGE";
		case PARAMETER_VALUE_TOO_HIGH: return "pilot.base.canopen.sdo_error_e.PARAMETER_VALUE_TOO_HIGH";
		case PARAMETER_VALUE_TOO_LOW: return "pilot.base.canopen.sdo_error_e.PARAMETER_VALUE_TOO_LOW";
		case PDO_LENGTH_EXCEEDED: return "pilot.base.canopen.sdo_error_e.PDO_LENGTH_EXCEEDED";
		case SERVICE_ERROR: return "pilot.base.canopen.sdo_error_e.SERVICE_ERROR";
		case SUB_INDEX_DOES_NOT_EXIST: return "pilot.base.canopen.sdo_error_e.SUB_INDEX_DOES_NOT_EXIST";
		case SUB_PARAMETER_VALUE_OUT_OF_RANGE: return "pilot.base.canopen.sdo_error_e.SUB_PARAMETER_VALUE_OUT_OF_RANGE";
		case TIMEOUT: return "pilot.base.canopen.sdo_error_e.TIMEOUT";
		case TOGGLE_BIT_ERROR: return "pilot.base.canopen.sdo_error_e.TOGGLE_BIT_ERROR";
		case TYPE_CONFLICT: return "pilot.base.canopen.sdo_error_e.TYPE_CONFLICT";
		case TYPE_MISMATCH: return "pilot.base.canopen.sdo_error_e.TYPE_MISMATCH";
	}
	return std::to_string(value);
}

void sdo_error_e::from_string(const std::string& _str) {
	std::string _name;
	vnx::from_string(_str, _name);
	from_string_value(_name);
}

void sdo_error_e::from_string_value(const std::string& _name) {
	vnx::Variant var;
	vnx::from_string_value(_name, var);
	if(var.is_string()) {
		if(_name == "ACCESS_ERROR") value = ACCESS_ERROR;
		else if(_name == "CANNOT_MAP_TO_PDO") value = CANNOT_MAP_TO_PDO;
		else if(_name == "CONNECTION_ERROR") value = CONNECTION_ERROR;
		else if(_name == "DATA_TRANSFER") value = DATA_TRANSFER;
		else if(_name == "DATA_TRANSFER_DEVICE_STATE") value = DATA_TRANSFER_DEVICE_STATE;
		else if(_name == "DATA_TRANSFER_LOCAL") value = DATA_TRANSFER_LOCAL;
		else if(_name == "GENERAL_ERROR") value = GENERAL_ERROR;
		else if(_name == "GENERAL_INTERNAL_INCOMPATIBILITY") value = GENERAL_INTERNAL_INCOMPATIBILITY;
		else if(_name == "GENERAL_PARAMETER_INCOMPATIBILITY") value = GENERAL_PARAMETER_INCOMPATIBILITY;
		else if(_name == "HARDWARE_FAULT") value = HARDWARE_FAULT;
		else if(_name == "ILLEGAL_PARAMETER") value = ILLEGAL_PARAMETER;
		else if(_name == "INDEX_RESERVED") value = INDEX_RESERVED;
		else if(_name == "INVALID_ADDRESS") value = INVALID_ADDRESS;
		else if(_name == "INVALID_BLOCK_CRC") value = INVALID_BLOCK_CRC;
		else if(_name == "INVALID_BLOCK_SEQUENCE_NUMBER") value = INVALID_BLOCK_SEQUENCE_NUMBER;
		else if(_name == "INVALID_BLOCK_SIZE") value = INVALID_BLOCK_SIZE;
		else if(_name == "INVALID_COMMAND") value = INVALID_COMMAND;
		else if(_name == "MAX_VALUE_LESS_THAN_MIN_VALUE") value = MAX_VALUE_LESS_THAN_MIN_VALUE;
		else if(_name == "NO_DATA") value = NO_DATA;
		else if(_name == "NO_ERROR") value = NO_ERROR;
		else if(_name == "OBJECT_ACCESS_READ_ONLY") value = OBJECT_ACCESS_READ_ONLY;
		else if(_name == "OBJECT_ACCESS_UNSUPPORTED") value = OBJECT_ACCESS_UNSUPPORTED;
		else if(_name == "OBJECT_ACCESS_WRITE_ONLY") value = OBJECT_ACCESS_WRITE_ONLY;
		else if(_name == "OBJECT_ATTRIBUTE_INCONSISTENT") value = OBJECT_ATTRIBUTE_INCONSISTENT;
		else if(_name == "OBJECT_DICTIONARY_FAIL") value = OBJECT_DICTIONARY_FAIL;
		else if(_name == "OBJECT_LENGTH_TOO_HIGH") value = OBJECT_LENGTH_TOO_HIGH;
		else if(_name == "OBJECT_LENGTH_TOO_LOW") value = OBJECT_LENGTH_TOO_LOW;
		else if(_name == "OBJECT_NON_EXISTENT") value = OBJECT_NON_EXISTENT;
		else if(_name == "OUT_OF_MEMORY") value = OUT_OF_MEMORY;
		else if(_name == "PARAMETER_INCONSISTENT") value = PARAMETER_INCONSISTENT;
		else if(_name == "PARAMETER_VALUE_OUT_OF_RANGE") value = PARAMETER_VALUE_OUT_OF_RANGE;
		else if(_name == "PARAMETER_VALUE_TOO_HIGH") value = PARAMETER_VALUE_TOO_HIGH;
		else if(_name == "PARAMETER_VALUE_TOO_LOW") value = PARAMETER_VALUE_TOO_LOW;
		else if(_name == "PDO_LENGTH_EXCEEDED") value = PDO_LENGTH_EXCEEDED;
		else if(_name == "SERVICE_ERROR") value = SERVICE_ERROR;
		else if(_name == "SUB_INDEX_DOES_NOT_EXIST") value = SUB_INDEX_DOES_NOT_EXIST;
		else if(_name == "SUB_PARAMETER_VALUE_OUT_OF_RANGE") value = SUB_PARAMETER_VALUE_OUT_OF_RANGE;
		else if(_name == "TIMEOUT") value = TIMEOUT;
		else if(_name == "TOGGLE_BIT_ERROR") value = TOGGLE_BIT_ERROR;
		else if(_name == "TYPE_CONFLICT") value = TYPE_CONFLICT;
		else if(_name == "TYPE_MISMATCH") value = TYPE_MISMATCH;
		else value = enum_t(vnx::hash64(_name));
	} else {
		value = enum_t(std::stoul(_name.c_str(), nullptr, 0));
	}
}

void sdo_error_e::accept(vnx::Visitor& _visitor) const {
	std::string _name;
	switch(value) {
		case ACCESS_ERROR: _name = "ACCESS_ERROR"; break;
		case CANNOT_MAP_TO_PDO: _name = "CANNOT_MAP_TO_PDO"; break;
		case CONNECTION_ERROR: _name = "CONNECTION_ERROR"; break;
		case DATA_TRANSFER: _name = "DATA_TRANSFER"; break;
		case DATA_TRANSFER_DEVICE_STATE: _name = "DATA_TRANSFER_DEVICE_STATE"; break;
		case DATA_TRANSFER_LOCAL: _name = "DATA_TRANSFER_LOCAL"; break;
		case GENERAL_ERROR: _name = "GENERAL_ERROR"; break;
		case GENERAL_INTERNAL_INCOMPATIBILITY: _name = "GENERAL_INTERNAL_INCOMPATIBILITY"; break;
		case GENERAL_PARAMETER_INCOMPATIBILITY: _name = "GENERAL_PARAMETER_INCOMPATIBILITY"; break;
		case HARDWARE_FAULT: _name = "HARDWARE_FAULT"; break;
		case ILLEGAL_PARAMETER: _name = "ILLEGAL_PARAMETER"; break;
		case INDEX_RESERVED: _name = "INDEX_RESERVED"; break;
		case INVALID_ADDRESS: _name = "INVALID_ADDRESS"; break;
		case INVALID_BLOCK_CRC: _name = "INVALID_BLOCK_CRC"; break;
		case INVALID_BLOCK_SEQUENCE_NUMBER: _name = "INVALID_BLOCK_SEQUENCE_NUMBER"; break;
		case INVALID_BLOCK_SIZE: _name = "INVALID_BLOCK_SIZE"; break;
		case INVALID_COMMAND: _name = "INVALID_COMMAND"; break;
		case MAX_VALUE_LESS_THAN_MIN_VALUE: _name = "MAX_VALUE_LESS_THAN_MIN_VALUE"; break;
		case NO_DATA: _name = "NO_DATA"; break;
		case NO_ERROR: _name = "NO_ERROR"; break;
		case OBJECT_ACCESS_READ_ONLY: _name = "OBJECT_ACCESS_READ_ONLY"; break;
		case OBJECT_ACCESS_UNSUPPORTED: _name = "OBJECT_ACCESS_UNSUPPORTED"; break;
		case OBJECT_ACCESS_WRITE_ONLY: _name = "OBJECT_ACCESS_WRITE_ONLY"; break;
		case OBJECT_ATTRIBUTE_INCONSISTENT: _name = "OBJECT_ATTRIBUTE_INCONSISTENT"; break;
		case OBJECT_DICTIONARY_FAIL: _name = "OBJECT_DICTIONARY_FAIL"; break;
		case OBJECT_LENGTH_TOO_HIGH: _name = "OBJECT_LENGTH_TOO_HIGH"; break;
		case OBJECT_LENGTH_TOO_LOW: _name = "OBJECT_LENGTH_TOO_LOW"; break;
		case OBJECT_NON_EXISTENT: _name = "OBJECT_NON_EXISTENT"; break;
		case OUT_OF_MEMORY: _name = "OUT_OF_MEMORY"; break;
		case PARAMETER_INCONSISTENT: _name = "PARAMETER_INCONSISTENT"; break;
		case PARAMETER_VALUE_OUT_OF_RANGE: _name = "PARAMETER_VALUE_OUT_OF_RANGE"; break;
		case PARAMETER_VALUE_TOO_HIGH: _name = "PARAMETER_VALUE_TOO_HIGH"; break;
		case PARAMETER_VALUE_TOO_LOW: _name = "PARAMETER_VALUE_TOO_LOW"; break;
		case PDO_LENGTH_EXCEEDED: _name = "PDO_LENGTH_EXCEEDED"; break;
		case SERVICE_ERROR: _name = "SERVICE_ERROR"; break;
		case SUB_INDEX_DOES_NOT_EXIST: _name = "SUB_INDEX_DOES_NOT_EXIST"; break;
		case SUB_PARAMETER_VALUE_OUT_OF_RANGE: _name = "SUB_PARAMETER_VALUE_OUT_OF_RANGE"; break;
		case TIMEOUT: _name = "TIMEOUT"; break;
		case TOGGLE_BIT_ERROR: _name = "TOGGLE_BIT_ERROR"; break;
		case TYPE_CONFLICT: _name = "TYPE_CONFLICT"; break;
		case TYPE_MISMATCH: _name = "TYPE_MISMATCH"; break;
	}
	_visitor.enum_value(value, _name);
}

void sdo_error_e::write(std::ostream& _out) const {
	switch(value) {
		case ACCESS_ERROR: _out << "\"ACCESS_ERROR\""; break;
		case CANNOT_MAP_TO_PDO: _out << "\"CANNOT_MAP_TO_PDO\""; break;
		case CONNECTION_ERROR: _out << "\"CONNECTION_ERROR\""; break;
		case DATA_TRANSFER: _out << "\"DATA_TRANSFER\""; break;
		case DATA_TRANSFER_DEVICE_STATE: _out << "\"DATA_TRANSFER_DEVICE_STATE\""; break;
		case DATA_TRANSFER_LOCAL: _out << "\"DATA_TRANSFER_LOCAL\""; break;
		case GENERAL_ERROR: _out << "\"GENERAL_ERROR\""; break;
		case GENERAL_INTERNAL_INCOMPATIBILITY: _out << "\"GENERAL_INTERNAL_INCOMPATIBILITY\""; break;
		case GENERAL_PARAMETER_INCOMPATIBILITY: _out << "\"GENERAL_PARAMETER_INCOMPATIBILITY\""; break;
		case HARDWARE_FAULT: _out << "\"HARDWARE_FAULT\""; break;
		case ILLEGAL_PARAMETER: _out << "\"ILLEGAL_PARAMETER\""; break;
		case INDEX_RESERVED: _out << "\"INDEX_RESERVED\""; break;
		case INVALID_ADDRESS: _out << "\"INVALID_ADDRESS\""; break;
		case INVALID_BLOCK_CRC: _out << "\"INVALID_BLOCK_CRC\""; break;
		case INVALID_BLOCK_SEQUENCE_NUMBER: _out << "\"INVALID_BLOCK_SEQUENCE_NUMBER\""; break;
		case INVALID_BLOCK_SIZE: _out << "\"INVALID_BLOCK_SIZE\""; break;
		case INVALID_COMMAND: _out << "\"INVALID_COMMAND\""; break;
		case MAX_VALUE_LESS_THAN_MIN_VALUE: _out << "\"MAX_VALUE_LESS_THAN_MIN_VALUE\""; break;
		case NO_DATA: _out << "\"NO_DATA\""; break;
		case NO_ERROR: _out << "\"NO_ERROR\""; break;
		case OBJECT_ACCESS_READ_ONLY: _out << "\"OBJECT_ACCESS_READ_ONLY\""; break;
		case OBJECT_ACCESS_UNSUPPORTED: _out << "\"OBJECT_ACCESS_UNSUPPORTED\""; break;
		case OBJECT_ACCESS_WRITE_ONLY: _out << "\"OBJECT_ACCESS_WRITE_ONLY\""; break;
		case OBJECT_ATTRIBUTE_INCONSISTENT: _out << "\"OBJECT_ATTRIBUTE_INCONSISTENT\""; break;
		case OBJECT_DICTIONARY_FAIL: _out << "\"OBJECT_DICTIONARY_FAIL\""; break;
		case OBJECT_LENGTH_TOO_HIGH: _out << "\"OBJECT_LENGTH_TOO_HIGH\""; break;
		case OBJECT_LENGTH_TOO_LOW: _out << "\"OBJECT_LENGTH_TOO_LOW\""; break;
		case OBJECT_NON_EXISTENT: _out << "\"OBJECT_NON_EXISTENT\""; break;
		case OUT_OF_MEMORY: _out << "\"OUT_OF_MEMORY\""; break;
		case PARAMETER_INCONSISTENT: _out << "\"PARAMETER_INCONSISTENT\""; break;
		case PARAMETER_VALUE_OUT_OF_RANGE: _out << "\"PARAMETER_VALUE_OUT_OF_RANGE\""; break;
		case PARAMETER_VALUE_TOO_HIGH: _out << "\"PARAMETER_VALUE_TOO_HIGH\""; break;
		case PARAMETER_VALUE_TOO_LOW: _out << "\"PARAMETER_VALUE_TOO_LOW\""; break;
		case PDO_LENGTH_EXCEEDED: _out << "\"PDO_LENGTH_EXCEEDED\""; break;
		case SERVICE_ERROR: _out << "\"SERVICE_ERROR\""; break;
		case SUB_INDEX_DOES_NOT_EXIST: _out << "\"SUB_INDEX_DOES_NOT_EXIST\""; break;
		case SUB_PARAMETER_VALUE_OUT_OF_RANGE: _out << "\"SUB_PARAMETER_VALUE_OUT_OF_RANGE\""; break;
		case TIMEOUT: _out << "\"TIMEOUT\""; break;
		case TOGGLE_BIT_ERROR: _out << "\"TOGGLE_BIT_ERROR\""; break;
		case TYPE_CONFLICT: _out << "\"TYPE_CONFLICT\""; break;
		case TYPE_MISMATCH: _out << "\"TYPE_MISMATCH\""; break;
		default: _out << value;
	}
}

void sdo_error_e::read(std::istream& _in) {
	from_string_value(vnx::read(_in).to_string_value());
}

vnx::Object sdo_error_e::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.canopen.sdo_error_e";
	_object["value"] = value;
	return _object;
}

void sdo_error_e::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "value") {
			_entry.second.to(value);
		}
	}
}

vnx::Variant sdo_error_e::get_field(const std::string& _name) const {
	if(_name == "value") {
		return vnx::Variant(value);
	}
	return vnx::Variant();
}

void sdo_error_e::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "value") {
		_value.to(value);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const sdo_error_e& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, sdo_error_e& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* sdo_error_e::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> sdo_error_e::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.canopen.sdo_error_e";
	type_code->type_hash = vnx::Hash64(0x9b27dfeddc64e9c2ull);
	type_code->code_hash = vnx::Hash64(0x20f19aa211c94138ull);
	type_code->is_native = true;
	type_code->is_enum = true;
	type_code->native_size = sizeof(::pilot::base::canopen::sdo_error_e);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<vnx::Struct<sdo_error_e>>(); };
	type_code->fields.resize(1);
	{
		auto& field = type_code->fields[0];
		field.data_size = 4;
		field.name = "value";
		field.code = {3};
	}
	type_code->enum_map[2983389154] = "ACCESS_ERROR";
	type_code->enum_map[102157286] = "CANNOT_MAP_TO_PDO";
	type_code->enum_map[983926906] = "CONNECTION_ERROR";
	type_code->enum_map[3212620913] = "DATA_TRANSFER";
	type_code->enum_map[1312520157] = "DATA_TRANSFER_DEVICE_STATE";
	type_code->enum_map[2084807517] = "DATA_TRANSFER_LOCAL";
	type_code->enum_map[2961084143] = "GENERAL_ERROR";
	type_code->enum_map[2100302596] = "GENERAL_INTERNAL_INCOMPATIBILITY";
	type_code->enum_map[2445333127] = "GENERAL_PARAMETER_INCOMPATIBILITY";
	type_code->enum_map[4172050110] = "HARDWARE_FAULT";
	type_code->enum_map[687006613] = "ILLEGAL_PARAMETER";
	type_code->enum_map[1401645979] = "INDEX_RESERVED";
	type_code->enum_map[2671328695] = "INVALID_ADDRESS";
	type_code->enum_map[958542662] = "INVALID_BLOCK_CRC";
	type_code->enum_map[1044192863] = "INVALID_BLOCK_SEQUENCE_NUMBER";
	type_code->enum_map[424332037] = "INVALID_BLOCK_SIZE";
	type_code->enum_map[2016579960] = "INVALID_COMMAND";
	type_code->enum_map[2572043046] = "MAX_VALUE_LESS_THAN_MIN_VALUE";
	type_code->enum_map[3860596597] = "NO_DATA";
	type_code->enum_map[134115394] = "NO_ERROR";
	type_code->enum_map[1579395730] = "OBJECT_ACCESS_READ_ONLY";
	type_code->enum_map[633315882] = "OBJECT_ACCESS_UNSUPPORTED";
	type_code->enum_map[275658749] = "OBJECT_ACCESS_WRITE_ONLY";
	type_code->enum_map[1032774329] = "OBJECT_ATTRIBUTE_INCONSISTENT";
	type_code->enum_map[576593538] = "OBJECT_DICTIONARY_FAIL";
	type_code->enum_map[3600225261] = "OBJECT_LENGTH_TOO_HIGH";
	type_code->enum_map[3544164810] = "OBJECT_LENGTH_TOO_LOW";
	type_code->enum_map[2188408222] = "OBJECT_NON_EXISTENT";
	type_code->enum_map[634510872] = "OUT_OF_MEMORY";
	type_code->enum_map[2919431651] = "PARAMETER_INCONSISTENT";
	type_code->enum_map[1441488625] = "PARAMETER_VALUE_OUT_OF_RANGE";
	type_code->enum_map[4275016742] = "PARAMETER_VALUE_TOO_HIGH";
	type_code->enum_map[1419246051] = "PARAMETER_VALUE_TOO_LOW";
	type_code->enum_map[722766574] = "PDO_LENGTH_EXCEEDED";
	type_code->enum_map[520912540] = "SERVICE_ERROR";
	type_code->enum_map[1435966880] = "SUB_INDEX_DOES_NOT_EXIST";
	type_code->enum_map[1995812059] = "SUB_PARAMETER_VALUE_OUT_OF_RANGE";
	type_code->enum_map[2481323511] = "TIMEOUT";
	type_code->enum_map[3556383544] = "TOGGLE_BIT_ERROR";
	type_code->enum_map[4291194971] = "TYPE_CONFLICT";
	type_code->enum_map[2316570480] = "TYPE_MISMATCH";
	type_code->build();
	return type_code;
}


} // namespace pilot
} // namespace base
} // namespace canopen


namespace vnx {

void read(TypeInput& in, ::pilot::base::canopen::sdo_error_e& value, const TypeCode* type_code, const uint16_t* code) {
	if(code) {
		switch(code[0]) {
			case CODE_OBJECT:
			case CODE_ALT_OBJECT: {
				Object tmp;
				vnx::read(in, tmp, type_code, code);
				value.from_object(tmp);
				return;
			}
			case CODE_DYNAMIC:
			case CODE_ALT_DYNAMIC:
				vnx::read_dynamic(in, value);
				return;
		}
	}
	if(!type_code) {
		Variant tmp;
		vnx::read(in, tmp, type_code, code);
		if(tmp.is_string()) {
			vnx::from_string(tmp.to_string(), value);
		} else if(tmp.is_ulong()) {
			value = ::pilot::base::canopen::sdo_error_e::enum_t(tmp.to<uint32_t>());
		} else {
			value = ::pilot::base::canopen::sdo_error_e();
		}
		return;
	}
	if(code) {
		switch(code[0]) {
			case CODE_STRUCT: type_code = type_code->depends[code[1]]; break;
			case CODE_ALT_STRUCT: type_code = type_code->depends[vnx::flip_bytes(code[1])]; break;
			default: {
				vnx::skip(in, type_code, code);
				return;
			}
		}
	}
	const char* const _buf = in.read(type_code->total_field_size);
	if(type_code->is_matched) {
		if(const auto* const _field = type_code->field_map[0]) {
			vnx::read_value(_buf + _field->offset, value.value, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::canopen::sdo_error_e& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_STRING) {
		vnx::write(out, value.to_string_value(), nullptr, code);
		return;
	}
	if(code && code[0] == CODE_UINT32) {
		vnx::write(out, value.value, nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::canopen::vnx_native_type_code_sdo_error_e;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::canopen::sdo_error_e>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(4);
	vnx::write_value(_buf + 0, value.value);
}

void read(std::istream& in, ::pilot::base::canopen::sdo_error_e& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::canopen::sdo_error_e& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::canopen::sdo_error_e& value) {
	value.accept(visitor);
}

void read(TypeInput& in, ::pilot::base::canopen::sdo_error_e::enum_t& value, const TypeCode* type_code, const uint16_t* code) {
	uint32_t tmp = 0;
	vnx::read(in, tmp, type_code, code);
	value = ::pilot::base::canopen::sdo_error_e::enum_t(tmp);
}

void write(TypeOutput& out, const ::pilot::base::canopen::sdo_error_e::enum_t& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::write(out, uint32_t(value), type_code, code);
}

template<>
std::string to_string(const ::pilot::base::canopen::sdo_error_e& _value) {
	return _value.to_string();
}

template<>
std::string to_string_value(const ::pilot::base::canopen::sdo_error_e& _value) {
	return _value.to_string_value();
}

template<>
std::string to_string_value_full(const ::pilot::base::canopen::sdo_error_e& _value) {
	return _value.to_string_value_full();
}

template<>
std::string to_string(const ::pilot::base::canopen::sdo_error_e::enum_t& _value) {
	return ::pilot::base::canopen::sdo_error_e(_value).to_string();
}

template<>
std::string to_string_value(const ::pilot::base::canopen::sdo_error_e::enum_t& _value) {
	return ::pilot::base::canopen::sdo_error_e(_value).to_string_value();
}

template<>
std::string to_string_value_full(const ::pilot::base::canopen::sdo_error_e::enum_t& _value) {
	return ::pilot::base::canopen::sdo_error_e(_value).to_string_value_full();
}

bool is_equivalent<::pilot::base::canopen::sdo_error_e>::operator()(const uint16_t* code, const TypeCode* type_code) {
	if(code[0] != CODE_STRUCT || !type_code) {
		return false;
	}
	type_code = type_code->depends[code[1]];
	return type_code->type_hash == ::pilot::base::canopen::sdo_error_e::VNX_TYPE_HASH && type_code->is_equivalent;
}

} // vnx

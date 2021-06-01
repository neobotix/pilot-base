
// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/UDP_ReceiverBase.hxx>
#include <vnx/NoSuchMethod.hxx>
#include <pilot/base/UDP_Receiver_close_port.hxx>
#include <pilot/base/UDP_Receiver_close_port_return.hxx>
#include <pilot/base/UDP_Receiver_open_port.hxx>
#include <pilot/base/UDP_Receiver_open_port_return.hxx>
#include <vnx/Module.h>
#include <vnx/ModuleInterface_vnx_get_config.hxx>
#include <vnx/ModuleInterface_vnx_get_config_return.hxx>
#include <vnx/ModuleInterface_vnx_get_config_object.hxx>
#include <vnx/ModuleInterface_vnx_get_config_object_return.hxx>
#include <vnx/ModuleInterface_vnx_get_module_info.hxx>
#include <vnx/ModuleInterface_vnx_get_module_info_return.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code_return.hxx>
#include <vnx/ModuleInterface_vnx_restart.hxx>
#include <vnx/ModuleInterface_vnx_restart_return.hxx>
#include <vnx/ModuleInterface_vnx_self_test.hxx>
#include <vnx/ModuleInterface_vnx_self_test_return.hxx>
#include <vnx/ModuleInterface_vnx_set_config.hxx>
#include <vnx/ModuleInterface_vnx_set_config_return.hxx>
#include <vnx/ModuleInterface_vnx_set_config_object.hxx>
#include <vnx/ModuleInterface_vnx_set_config_object_return.hxx>
#include <vnx/ModuleInterface_vnx_stop.hxx>
#include <vnx/ModuleInterface_vnx_stop_return.hxx>
#include <vnx/TopicPtr.hpp>

#include <vnx/vnx.h>


namespace pilot {
namespace base {


const vnx::Hash64 UDP_ReceiverBase::VNX_TYPE_HASH(0x5c0111dff18f907bull);
const vnx::Hash64 UDP_ReceiverBase::VNX_CODE_HASH(0xbd1a3b1a2ee79869ull);

UDP_ReceiverBase::UDP_ReceiverBase(const std::string& _vnx_name)
	:	Module::Module(_vnx_name)
{
	vnx::read_config(vnx_name + ".output", output);
	vnx::read_config(vnx_name + ".port", port);
	vnx::read_config(vnx_name + ".max_packet_size", max_packet_size);
	vnx::read_config(vnx_name + ".read_timeout_ms", read_timeout_ms);
	vnx::read_config(vnx_name + ".error_interval_ms", error_interval_ms);
	vnx::read_config(vnx_name + ".stats_interval_ms", stats_interval_ms);
}

vnx::Hash64 UDP_ReceiverBase::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string UDP_ReceiverBase::get_type_name() const {
	return "pilot.base.UDP_Receiver";
}

const vnx::TypeCode* UDP_ReceiverBase::get_type_code() const {
	return pilot::base::vnx_native_type_code_UDP_ReceiverBase;
}

void UDP_ReceiverBase::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = pilot::base::vnx_native_type_code_UDP_ReceiverBase;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, output);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, port);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, max_packet_size);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, read_timeout_ms);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, error_interval_ms);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, stats_interval_ms);
	_visitor.type_end(*_type_code);
}

void UDP_ReceiverBase::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"output\": "; vnx::write(_out, output);
	_out << ", \"port\": "; vnx::write(_out, port);
	_out << ", \"max_packet_size\": "; vnx::write(_out, max_packet_size);
	_out << ", \"read_timeout_ms\": "; vnx::write(_out, read_timeout_ms);
	_out << ", \"error_interval_ms\": "; vnx::write(_out, error_interval_ms);
	_out << ", \"stats_interval_ms\": "; vnx::write(_out, stats_interval_ms);
	_out << "}";
}

void UDP_ReceiverBase::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object UDP_ReceiverBase::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.UDP_Receiver";
	_object["output"] = output;
	_object["port"] = port;
	_object["max_packet_size"] = max_packet_size;
	_object["read_timeout_ms"] = read_timeout_ms;
	_object["error_interval_ms"] = error_interval_ms;
	_object["stats_interval_ms"] = stats_interval_ms;
	return _object;
}

void UDP_ReceiverBase::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "error_interval_ms") {
			_entry.second.to(error_interval_ms);
		} else if(_entry.first == "max_packet_size") {
			_entry.second.to(max_packet_size);
		} else if(_entry.first == "output") {
			_entry.second.to(output);
		} else if(_entry.first == "port") {
			_entry.second.to(port);
		} else if(_entry.first == "read_timeout_ms") {
			_entry.second.to(read_timeout_ms);
		} else if(_entry.first == "stats_interval_ms") {
			_entry.second.to(stats_interval_ms);
		}
	}
}

vnx::Variant UDP_ReceiverBase::get_field(const std::string& _name) const {
	if(_name == "output") {
		return vnx::Variant(output);
	}
	if(_name == "port") {
		return vnx::Variant(port);
	}
	if(_name == "max_packet_size") {
		return vnx::Variant(max_packet_size);
	}
	if(_name == "read_timeout_ms") {
		return vnx::Variant(read_timeout_ms);
	}
	if(_name == "error_interval_ms") {
		return vnx::Variant(error_interval_ms);
	}
	if(_name == "stats_interval_ms") {
		return vnx::Variant(stats_interval_ms);
	}
	return vnx::Variant();
}

void UDP_ReceiverBase::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "output") {
		_value.to(output);
	} else if(_name == "port") {
		_value.to(port);
	} else if(_name == "max_packet_size") {
		_value.to(max_packet_size);
	} else if(_name == "read_timeout_ms") {
		_value.to(read_timeout_ms);
	} else if(_name == "error_interval_ms") {
		_value.to(error_interval_ms);
	} else if(_name == "stats_interval_ms") {
		_value.to(stats_interval_ms);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const UDP_ReceiverBase& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, UDP_ReceiverBase& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* UDP_ReceiverBase::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> UDP_ReceiverBase::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.UDP_Receiver";
	type_code->type_hash = vnx::Hash64(0x5c0111dff18f907bull);
	type_code->code_hash = vnx::Hash64(0xbd1a3b1a2ee79869ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::pilot::base::UDP_ReceiverBase);
	type_code->methods.resize(11);
	type_code->methods[0] = ::vnx::ModuleInterface_vnx_get_config_object::static_get_type_code();
	type_code->methods[1] = ::vnx::ModuleInterface_vnx_get_config::static_get_type_code();
	type_code->methods[2] = ::vnx::ModuleInterface_vnx_set_config_object::static_get_type_code();
	type_code->methods[3] = ::vnx::ModuleInterface_vnx_set_config::static_get_type_code();
	type_code->methods[4] = ::vnx::ModuleInterface_vnx_get_type_code::static_get_type_code();
	type_code->methods[5] = ::vnx::ModuleInterface_vnx_get_module_info::static_get_type_code();
	type_code->methods[6] = ::vnx::ModuleInterface_vnx_restart::static_get_type_code();
	type_code->methods[7] = ::vnx::ModuleInterface_vnx_stop::static_get_type_code();
	type_code->methods[8] = ::vnx::ModuleInterface_vnx_self_test::static_get_type_code();
	type_code->methods[9] = ::pilot::base::UDP_Receiver_open_port::static_get_type_code();
	type_code->methods[10] = ::pilot::base::UDP_Receiver_close_port::static_get_type_code();
	type_code->fields.resize(6);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "output";
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 4;
		field.name = "port";
		field.code = {7};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 4;
		field.name = "max_packet_size";
		field.value = vnx::to_string(65536);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[3];
		field.data_size = 4;
		field.name = "read_timeout_ms";
		field.value = vnx::to_string(200);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[4];
		field.data_size = 4;
		field.name = "error_interval_ms";
		field.value = vnx::to_string(1000);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[5];
		field.data_size = 4;
		field.name = "stats_interval_ms";
		field.value = vnx::to_string(10000);
		field.code = {7};
	}
	type_code->build();
	return type_code;
}

void UDP_ReceiverBase::vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) {
	const auto* _type_code = _value->get_type_code();
	while(_type_code) {
		switch(_type_code->type_hash) {
			default:
				_type_code = _type_code->super;
		}
	}
	handle(std::static_pointer_cast<const vnx::Value>(_value));
}

std::shared_ptr<vnx::Value> UDP_ReceiverBase::vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) {
	switch(_method->get_type_hash()) {
		case 0x17f58f68bf83abc0ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_config_object>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_config_object_return::create();
			_return_value->_ret_0 = vnx_get_config_object();
			return _return_value;
		}
		case 0xbbc7f1a01044d294ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_config>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_config_return::create();
			_return_value->_ret_0 = vnx_get_config(_args->name);
			return _return_value;
		}
		case 0xca30f814f17f322full: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_set_config_object>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_set_config_object_return::create();
			vnx_set_config_object(_args->config);
			return _return_value;
		}
		case 0x362aac91373958b7ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_set_config>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_set_config_return::create();
			vnx_set_config(_args->name, _args->value);
			return _return_value;
		}
		case 0x305ec4d628960e5dull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_type_code>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_type_code_return::create();
			_return_value->_ret_0 = vnx_get_type_code();
			return _return_value;
		}
		case 0xf6d82bdf66d034a1ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_module_info>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_module_info_return::create();
			_return_value->_ret_0 = vnx_get_module_info();
			return _return_value;
		}
		case 0x9e95dc280cecca1bull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_restart>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_restart_return::create();
			vnx_restart();
			return _return_value;
		}
		case 0x7ab49ce3d1bfc0d2ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_stop>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_stop_return::create();
			vnx_stop();
			return _return_value;
		}
		case 0x6ce3775b41a42697ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_self_test>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_self_test_return::create();
			_return_value->_ret_0 = vnx_self_test();
			return _return_value;
		}
		case 0xc54c97600d1fd67eull: {
			auto _args = std::static_pointer_cast<const ::pilot::base::UDP_Receiver_open_port>(_method);
			auto _return_value = ::pilot::base::UDP_Receiver_open_port_return::create();
			open_port();
			return _return_value;
		}
		case 0x8efa3a2c8d9bf9edull: {
			auto _args = std::static_pointer_cast<const ::pilot::base::UDP_Receiver_close_port>(_method);
			auto _return_value = ::pilot::base::UDP_Receiver_close_port_return::create();
			close_port();
			return _return_value;
		}
	}
	auto _ex = vnx::NoSuchMethod::create();
	_ex->dst_mac = vnx_request ? vnx_request->dst_mac : vnx::Hash64();
	_ex->method = _method->get_type_name();
	return _ex;
}


} // namespace pilot
} // namespace base


namespace vnx {

void read(TypeInput& in, ::pilot::base::UDP_ReceiverBase& value, const TypeCode* type_code, const uint16_t* code) {
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
		vnx::skip(in, type_code, code);
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
		if(const auto* const _field = type_code->field_map[1]) {
			vnx::read_value(_buf + _field->offset, value.port, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.max_packet_size, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[3]) {
			vnx::read_value(_buf + _field->offset, value.read_timeout_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[4]) {
			vnx::read_value(_buf + _field->offset, value.error_interval_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[5]) {
			vnx::read_value(_buf + _field->offset, value.stats_interval_ms, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.output, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::UDP_ReceiverBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::vnx_native_type_code_UDP_ReceiverBase;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::UDP_ReceiverBase>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(20);
	vnx::write_value(_buf + 0, value.port);
	vnx::write_value(_buf + 4, value.max_packet_size);
	vnx::write_value(_buf + 8, value.read_timeout_ms);
	vnx::write_value(_buf + 12, value.error_interval_ms);
	vnx::write_value(_buf + 16, value.stats_interval_ms);
	vnx::write(out, value.output, type_code, type_code->fields[0].code.data());
}

void read(std::istream& in, ::pilot::base::UDP_ReceiverBase& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::UDP_ReceiverBase& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::UDP_ReceiverBase& value) {
	value.accept(visitor);
}

} // vnx

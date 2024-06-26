
// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/NetworkStreamBase.hxx>
#include <vnx/NoSuchMethod.hxx>
#include <pilot/base/DataPacket.hxx>
#include <pilot/base/NetworkStream_connect.hxx>
#include <pilot/base/NetworkStream_connect_return.hxx>
#include <pilot/base/NetworkStream_disconnect.hxx>
#include <pilot/base/NetworkStream_disconnect_return.hxx>
#include <pilot/base/NetworkStream_is_connected.hxx>
#include <pilot/base/NetworkStream_is_connected_return.hxx>
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


const vnx::Hash64 NetworkStreamBase::VNX_TYPE_HASH(0xf148d90d9b345113ull);
const vnx::Hash64 NetworkStreamBase::VNX_CODE_HASH(0x90ce0dbec6a7dc78ull);

NetworkStreamBase::NetworkStreamBase(const std::string& _vnx_name)
	:	Module::Module(_vnx_name)
{
	vnx::read_config(vnx_name + ".input", input);
	vnx::read_config(vnx_name + ".output", output);
	vnx::read_config(vnx_name + ".address", address);
	vnx::read_config(vnx_name + ".read_buffer_size", read_buffer_size);
	vnx::read_config(vnx_name + ".stats_interval_ms", stats_interval_ms);
	vnx::read_config(vnx_name + ".error_interval_ms", error_interval_ms);
	vnx::read_config(vnx_name + ".shutdown_delay_ms", shutdown_delay_ms);
}

vnx::Hash64 NetworkStreamBase::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string NetworkStreamBase::get_type_name() const {
	return "pilot.base.NetworkStream";
}

const vnx::TypeCode* NetworkStreamBase::get_type_code() const {
	return pilot::base::vnx_native_type_code_NetworkStreamBase;
}

void NetworkStreamBase::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = pilot::base::vnx_native_type_code_NetworkStreamBase;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, input);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, output);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, address);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, read_buffer_size);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, stats_interval_ms);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, error_interval_ms);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, shutdown_delay_ms);
	_visitor.type_end(*_type_code);
}

void NetworkStreamBase::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"input\": "; vnx::write(_out, input);
	_out << ", \"output\": "; vnx::write(_out, output);
	_out << ", \"address\": "; vnx::write(_out, address);
	_out << ", \"read_buffer_size\": "; vnx::write(_out, read_buffer_size);
	_out << ", \"stats_interval_ms\": "; vnx::write(_out, stats_interval_ms);
	_out << ", \"error_interval_ms\": "; vnx::write(_out, error_interval_ms);
	_out << ", \"shutdown_delay_ms\": "; vnx::write(_out, shutdown_delay_ms);
	_out << "}";
}

void NetworkStreamBase::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object NetworkStreamBase::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.NetworkStream";
	_object["input"] = input;
	_object["output"] = output;
	_object["address"] = address;
	_object["read_buffer_size"] = read_buffer_size;
	_object["stats_interval_ms"] = stats_interval_ms;
	_object["error_interval_ms"] = error_interval_ms;
	_object["shutdown_delay_ms"] = shutdown_delay_ms;
	return _object;
}

void NetworkStreamBase::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "address") {
			_entry.second.to(address);
		} else if(_entry.first == "error_interval_ms") {
			_entry.second.to(error_interval_ms);
		} else if(_entry.first == "input") {
			_entry.second.to(input);
		} else if(_entry.first == "output") {
			_entry.second.to(output);
		} else if(_entry.first == "read_buffer_size") {
			_entry.second.to(read_buffer_size);
		} else if(_entry.first == "shutdown_delay_ms") {
			_entry.second.to(shutdown_delay_ms);
		} else if(_entry.first == "stats_interval_ms") {
			_entry.second.to(stats_interval_ms);
		}
	}
}

vnx::Variant NetworkStreamBase::get_field(const std::string& _name) const {
	if(_name == "input") {
		return vnx::Variant(input);
	}
	if(_name == "output") {
		return vnx::Variant(output);
	}
	if(_name == "address") {
		return vnx::Variant(address);
	}
	if(_name == "read_buffer_size") {
		return vnx::Variant(read_buffer_size);
	}
	if(_name == "stats_interval_ms") {
		return vnx::Variant(stats_interval_ms);
	}
	if(_name == "error_interval_ms") {
		return vnx::Variant(error_interval_ms);
	}
	if(_name == "shutdown_delay_ms") {
		return vnx::Variant(shutdown_delay_ms);
	}
	return vnx::Variant();
}

void NetworkStreamBase::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "input") {
		_value.to(input);
	} else if(_name == "output") {
		_value.to(output);
	} else if(_name == "address") {
		_value.to(address);
	} else if(_name == "read_buffer_size") {
		_value.to(read_buffer_size);
	} else if(_name == "stats_interval_ms") {
		_value.to(stats_interval_ms);
	} else if(_name == "error_interval_ms") {
		_value.to(error_interval_ms);
	} else if(_name == "shutdown_delay_ms") {
		_value.to(shutdown_delay_ms);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const NetworkStreamBase& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, NetworkStreamBase& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* NetworkStreamBase::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> NetworkStreamBase::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.NetworkStream";
	type_code->type_hash = vnx::Hash64(0xf148d90d9b345113ull);
	type_code->code_hash = vnx::Hash64(0x90ce0dbec6a7dc78ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::pilot::base::NetworkStreamBase);
	type_code->methods.resize(12);
	type_code->methods[0] = ::vnx::ModuleInterface_vnx_get_config_object::static_get_type_code();
	type_code->methods[1] = ::vnx::ModuleInterface_vnx_get_config::static_get_type_code();
	type_code->methods[2] = ::vnx::ModuleInterface_vnx_set_config_object::static_get_type_code();
	type_code->methods[3] = ::vnx::ModuleInterface_vnx_set_config::static_get_type_code();
	type_code->methods[4] = ::vnx::ModuleInterface_vnx_get_type_code::static_get_type_code();
	type_code->methods[5] = ::vnx::ModuleInterface_vnx_get_module_info::static_get_type_code();
	type_code->methods[6] = ::vnx::ModuleInterface_vnx_restart::static_get_type_code();
	type_code->methods[7] = ::vnx::ModuleInterface_vnx_stop::static_get_type_code();
	type_code->methods[8] = ::vnx::ModuleInterface_vnx_self_test::static_get_type_code();
	type_code->methods[9] = ::pilot::base::NetworkStream_is_connected::static_get_type_code();
	type_code->methods[10] = ::pilot::base::NetworkStream_connect::static_get_type_code();
	type_code->methods[11] = ::pilot::base::NetworkStream_disconnect::static_get_type_code();
	type_code->fields.resize(7);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "input";
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[1];
		field.is_extended = true;
		field.name = "output";
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[2];
		field.is_extended = true;
		field.name = "address";
		field.code = {32};
	}
	{
		auto& field = type_code->fields[3];
		field.data_size = 4;
		field.name = "read_buffer_size";
		field.value = vnx::to_string(4096);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[4];
		field.data_size = 4;
		field.name = "stats_interval_ms";
		field.value = vnx::to_string(10000);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[5];
		field.data_size = 4;
		field.name = "error_interval_ms";
		field.value = vnx::to_string(1000);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[6];
		field.data_size = 4;
		field.name = "shutdown_delay_ms";
		field.value = vnx::to_string(200);
		field.code = {7};
	}
	type_code->build();
	return type_code;
}

void NetworkStreamBase::vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) {
	const auto* _type_code = _value->get_type_code();
	while(_type_code) {
		switch(_type_code->type_hash) {
			case 0xcd0d2bd202ac0fb0ull:
				handle(std::static_pointer_cast<const ::pilot::base::DataPacket>(_value));
				return;
			default:
				_type_code = _type_code->super;
		}
	}
	handle(std::static_pointer_cast<const vnx::Value>(_value));
}

std::shared_ptr<vnx::Value> NetworkStreamBase::vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) {
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
		case 0x43ce78fb38d0a151ull: {
			auto _args = std::static_pointer_cast<const ::pilot::base::NetworkStream_is_connected>(_method);
			auto _return_value = ::pilot::base::NetworkStream_is_connected_return::create();
			_return_value->_ret_0 = is_connected();
			return _return_value;
		}
		case 0x5d1ba9f28b73deffull: {
			auto _args = std::static_pointer_cast<const ::pilot::base::NetworkStream_connect>(_method);
			auto _return_value = ::pilot::base::NetworkStream_connect_return::create();
			connect();
			return _return_value;
		}
		case 0x717989a7028c00b8ull: {
			auto _args = std::static_pointer_cast<const ::pilot::base::NetworkStream_disconnect>(_method);
			auto _return_value = ::pilot::base::NetworkStream_disconnect_return::create();
			disconnect();
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

void read(TypeInput& in, ::pilot::base::NetworkStreamBase& value, const TypeCode* type_code, const uint16_t* code) {
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
		if(const auto* const _field = type_code->field_map[3]) {
			vnx::read_value(_buf + _field->offset, value.read_buffer_size, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[4]) {
			vnx::read_value(_buf + _field->offset, value.stats_interval_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[5]) {
			vnx::read_value(_buf + _field->offset, value.error_interval_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[6]) {
			vnx::read_value(_buf + _field->offset, value.shutdown_delay_ms, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.input, type_code, _field->code.data()); break;
			case 1: vnx::read(in, value.output, type_code, _field->code.data()); break;
			case 2: vnx::read(in, value.address, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::NetworkStreamBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::vnx_native_type_code_NetworkStreamBase;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::NetworkStreamBase>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(16);
	vnx::write_value(_buf + 0, value.read_buffer_size);
	vnx::write_value(_buf + 4, value.stats_interval_ms);
	vnx::write_value(_buf + 8, value.error_interval_ms);
	vnx::write_value(_buf + 12, value.shutdown_delay_ms);
	vnx::write(out, value.input, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.output, type_code, type_code->fields[1].code.data());
	vnx::write(out, value.address, type_code, type_code->fields[2].code.data());
}

void read(std::istream& in, ::pilot::base::NetworkStreamBase& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::NetworkStreamBase& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::NetworkStreamBase& value) {
	value.accept(visitor);
}

} // vnx


// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/CAN_ProxyBase.hxx>
#include <vnx/NoSuchMethod.hxx>
#include <pilot/base/CAN_Frame.hxx>
#include <pilot/base/CAN_Proxy_send.hxx>
#include <pilot/base/CAN_Proxy_send_return.hxx>
#include <pilot/base/can_adapter_e.hxx>
#include <pilot/base/socketcan_options_t.hxx>
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


const vnx::Hash64 CAN_ProxyBase::VNX_TYPE_HASH(0x17c6e6ba3900a740ull);
const vnx::Hash64 CAN_ProxyBase::VNX_CODE_HASH(0xb53e75c7d299d2ceull);

CAN_ProxyBase::CAN_ProxyBase(const std::string& _vnx_name)
	:	Module::Module(_vnx_name)
{
	vnx::read_config(vnx_name + ".input", input);
	vnx::read_config(vnx_name + ".output", output);
	vnx::read_config(vnx_name + ".output_error", output_error);
	vnx::read_config(vnx_name + ".adapter", adapter);
	vnx::read_config(vnx_name + ".device", device);
	vnx::read_config(vnx_name + ".baud_rate", baud_rate);
	vnx::read_config(vnx_name + ".is_big_endian", is_big_endian);
	vnx::read_config(vnx_name + ".socket_options", socket_options);
	vnx::read_config(vnx_name + ".read_timeout_ms", read_timeout_ms);
	vnx::read_config(vnx_name + ".shutdown_delay_ms", shutdown_delay_ms);
	vnx::read_config(vnx_name + ".stats_interval_ms", stats_interval_ms);
}

vnx::Hash64 CAN_ProxyBase::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string CAN_ProxyBase::get_type_name() const {
	return "pilot.base.CAN_Proxy";
}

const vnx::TypeCode* CAN_ProxyBase::get_type_code() const {
	return pilot::base::vnx_native_type_code_CAN_ProxyBase;
}

void CAN_ProxyBase::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = pilot::base::vnx_native_type_code_CAN_ProxyBase;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, input);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, output);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, output_error);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, adapter);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, device);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, baud_rate);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, is_big_endian);
	_visitor.type_field(_type_code->fields[7], 7); vnx::accept(_visitor, socket_options);
	_visitor.type_field(_type_code->fields[8], 8); vnx::accept(_visitor, read_timeout_ms);
	_visitor.type_field(_type_code->fields[9], 9); vnx::accept(_visitor, shutdown_delay_ms);
	_visitor.type_field(_type_code->fields[10], 10); vnx::accept(_visitor, stats_interval_ms);
	_visitor.type_end(*_type_code);
}

void CAN_ProxyBase::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"input\": "; vnx::write(_out, input);
	_out << ", \"output\": "; vnx::write(_out, output);
	_out << ", \"output_error\": "; vnx::write(_out, output_error);
	_out << ", \"adapter\": "; vnx::write(_out, adapter);
	_out << ", \"device\": "; vnx::write(_out, device);
	_out << ", \"baud_rate\": "; vnx::write(_out, baud_rate);
	_out << ", \"is_big_endian\": "; vnx::write(_out, is_big_endian);
	_out << ", \"socket_options\": "; vnx::write(_out, socket_options);
	_out << ", \"read_timeout_ms\": "; vnx::write(_out, read_timeout_ms);
	_out << ", \"shutdown_delay_ms\": "; vnx::write(_out, shutdown_delay_ms);
	_out << ", \"stats_interval_ms\": "; vnx::write(_out, stats_interval_ms);
	_out << "}";
}

void CAN_ProxyBase::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object CAN_ProxyBase::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.CAN_Proxy";
	_object["input"] = input;
	_object["output"] = output;
	_object["output_error"] = output_error;
	_object["adapter"] = adapter;
	_object["device"] = device;
	_object["baud_rate"] = baud_rate;
	_object["is_big_endian"] = is_big_endian;
	_object["socket_options"] = socket_options;
	_object["read_timeout_ms"] = read_timeout_ms;
	_object["shutdown_delay_ms"] = shutdown_delay_ms;
	_object["stats_interval_ms"] = stats_interval_ms;
	return _object;
}

void CAN_ProxyBase::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "adapter") {
			_entry.second.to(adapter);
		} else if(_entry.first == "baud_rate") {
			_entry.second.to(baud_rate);
		} else if(_entry.first == "device") {
			_entry.second.to(device);
		} else if(_entry.first == "input") {
			_entry.second.to(input);
		} else if(_entry.first == "is_big_endian") {
			_entry.second.to(is_big_endian);
		} else if(_entry.first == "output") {
			_entry.second.to(output);
		} else if(_entry.first == "output_error") {
			_entry.second.to(output_error);
		} else if(_entry.first == "read_timeout_ms") {
			_entry.second.to(read_timeout_ms);
		} else if(_entry.first == "shutdown_delay_ms") {
			_entry.second.to(shutdown_delay_ms);
		} else if(_entry.first == "socket_options") {
			_entry.second.to(socket_options);
		} else if(_entry.first == "stats_interval_ms") {
			_entry.second.to(stats_interval_ms);
		}
	}
}

vnx::Variant CAN_ProxyBase::get_field(const std::string& _name) const {
	if(_name == "input") {
		return vnx::Variant(input);
	}
	if(_name == "output") {
		return vnx::Variant(output);
	}
	if(_name == "output_error") {
		return vnx::Variant(output_error);
	}
	if(_name == "adapter") {
		return vnx::Variant(adapter);
	}
	if(_name == "device") {
		return vnx::Variant(device);
	}
	if(_name == "baud_rate") {
		return vnx::Variant(baud_rate);
	}
	if(_name == "is_big_endian") {
		return vnx::Variant(is_big_endian);
	}
	if(_name == "socket_options") {
		return vnx::Variant(socket_options);
	}
	if(_name == "read_timeout_ms") {
		return vnx::Variant(read_timeout_ms);
	}
	if(_name == "shutdown_delay_ms") {
		return vnx::Variant(shutdown_delay_ms);
	}
	if(_name == "stats_interval_ms") {
		return vnx::Variant(stats_interval_ms);
	}
	return vnx::Variant();
}

void CAN_ProxyBase::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "input") {
		_value.to(input);
	} else if(_name == "output") {
		_value.to(output);
	} else if(_name == "output_error") {
		_value.to(output_error);
	} else if(_name == "adapter") {
		_value.to(adapter);
	} else if(_name == "device") {
		_value.to(device);
	} else if(_name == "baud_rate") {
		_value.to(baud_rate);
	} else if(_name == "is_big_endian") {
		_value.to(is_big_endian);
	} else if(_name == "socket_options") {
		_value.to(socket_options);
	} else if(_name == "read_timeout_ms") {
		_value.to(read_timeout_ms);
	} else if(_name == "shutdown_delay_ms") {
		_value.to(shutdown_delay_ms);
	} else if(_name == "stats_interval_ms") {
		_value.to(stats_interval_ms);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const CAN_ProxyBase& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, CAN_ProxyBase& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* CAN_ProxyBase::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> CAN_ProxyBase::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.CAN_Proxy";
	type_code->type_hash = vnx::Hash64(0x17c6e6ba3900a740ull);
	type_code->code_hash = vnx::Hash64(0xb53e75c7d299d2ceull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::pilot::base::CAN_ProxyBase);
	type_code->depends.resize(2);
	type_code->depends[0] = ::pilot::base::can_adapter_e::static_get_type_code();
	type_code->depends[1] = ::pilot::base::socketcan_options_t::static_get_type_code();
	type_code->methods.resize(10);
	type_code->methods[0] = ::vnx::ModuleInterface_vnx_get_config_object::static_get_type_code();
	type_code->methods[1] = ::vnx::ModuleInterface_vnx_get_config::static_get_type_code();
	type_code->methods[2] = ::vnx::ModuleInterface_vnx_set_config_object::static_get_type_code();
	type_code->methods[3] = ::vnx::ModuleInterface_vnx_set_config::static_get_type_code();
	type_code->methods[4] = ::vnx::ModuleInterface_vnx_get_type_code::static_get_type_code();
	type_code->methods[5] = ::vnx::ModuleInterface_vnx_get_module_info::static_get_type_code();
	type_code->methods[6] = ::vnx::ModuleInterface_vnx_restart::static_get_type_code();
	type_code->methods[7] = ::vnx::ModuleInterface_vnx_stop::static_get_type_code();
	type_code->methods[8] = ::vnx::ModuleInterface_vnx_self_test::static_get_type_code();
	type_code->methods[9] = ::pilot::base::CAN_Proxy_send::static_get_type_code();
	type_code->fields.resize(11);
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
		field.name = "output_error";
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "adapter";
		field.value = vnx::to_string("SOCKETCAN");
		field.code = {19, 0};
	}
	{
		auto& field = type_code->fields[4];
		field.is_extended = true;
		field.name = "device";
		field.code = {32};
	}
	{
		auto& field = type_code->fields[5];
		field.data_size = 4;
		field.name = "baud_rate";
		field.code = {7};
	}
	{
		auto& field = type_code->fields[6];
		field.data_size = 1;
		field.name = "is_big_endian";
		field.code = {31};
	}
	{
		auto& field = type_code->fields[7];
		field.is_extended = true;
		field.name = "socket_options";
		field.code = {19, 1};
	}
	{
		auto& field = type_code->fields[8];
		field.data_size = 4;
		field.name = "read_timeout_ms";
		field.value = vnx::to_string(200);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[9];
		field.data_size = 4;
		field.name = "shutdown_delay_ms";
		field.value = vnx::to_string(200);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[10];
		field.data_size = 4;
		field.name = "stats_interval_ms";
		field.value = vnx::to_string(10000);
		field.code = {7};
	}
	type_code->build();
	return type_code;
}

void CAN_ProxyBase::vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) {
	const auto* _type_code = _value->get_type_code();
	while(_type_code) {
		switch(_type_code->type_hash) {
			case 0x4d70a2725dc4def6ull:
				handle(std::static_pointer_cast<const ::pilot::base::CAN_Frame>(_value));
				return;
			default:
				_type_code = _type_code->super;
		}
	}
	handle(std::static_pointer_cast<const vnx::Value>(_value));
}

std::shared_ptr<vnx::Value> CAN_ProxyBase::vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) {
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
		case 0xfac9f3d0e6b114e0ull: {
			auto _args = std::static_pointer_cast<const ::pilot::base::CAN_Proxy_send>(_method);
			auto _return_value = ::pilot::base::CAN_Proxy_send_return::create();
			send(_args->frame);
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

void read(TypeInput& in, ::pilot::base::CAN_ProxyBase& value, const TypeCode* type_code, const uint16_t* code) {
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
		if(const auto* const _field = type_code->field_map[5]) {
			vnx::read_value(_buf + _field->offset, value.baud_rate, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[6]) {
			vnx::read_value(_buf + _field->offset, value.is_big_endian, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[8]) {
			vnx::read_value(_buf + _field->offset, value.read_timeout_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[9]) {
			vnx::read_value(_buf + _field->offset, value.shutdown_delay_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[10]) {
			vnx::read_value(_buf + _field->offset, value.stats_interval_ms, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.input, type_code, _field->code.data()); break;
			case 1: vnx::read(in, value.output, type_code, _field->code.data()); break;
			case 2: vnx::read(in, value.output_error, type_code, _field->code.data()); break;
			case 3: vnx::read(in, value.adapter, type_code, _field->code.data()); break;
			case 4: vnx::read(in, value.device, type_code, _field->code.data()); break;
			case 7: vnx::read(in, value.socket_options, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::CAN_ProxyBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::vnx_native_type_code_CAN_ProxyBase;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::CAN_ProxyBase>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(17);
	vnx::write_value(_buf + 0, value.baud_rate);
	vnx::write_value(_buf + 4, value.is_big_endian);
	vnx::write_value(_buf + 5, value.read_timeout_ms);
	vnx::write_value(_buf + 9, value.shutdown_delay_ms);
	vnx::write_value(_buf + 13, value.stats_interval_ms);
	vnx::write(out, value.input, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.output, type_code, type_code->fields[1].code.data());
	vnx::write(out, value.output_error, type_code, type_code->fields[2].code.data());
	vnx::write(out, value.adapter, type_code, type_code->fields[3].code.data());
	vnx::write(out, value.device, type_code, type_code->fields[4].code.data());
	vnx::write(out, value.socket_options, type_code, type_code->fields[7].code.data());
}

void read(std::istream& in, ::pilot::base::CAN_ProxyBase& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::CAN_ProxyBase& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::CAN_ProxyBase& value) {
	value.accept(visitor);
}

} // vnx

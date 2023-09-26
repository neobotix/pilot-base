
// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/UDP_SenderBase.hxx>
#include <vnx/NoSuchMethod.hxx>
#include <pilot/base/DataPacket.hxx>
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


const vnx::Hash64 UDP_SenderBase::VNX_TYPE_HASH(0xdefb7c71f4bfa0a0ull);
const vnx::Hash64 UDP_SenderBase::VNX_CODE_HASH(0x2012475c1d276238ull);

UDP_SenderBase::UDP_SenderBase(const std::string& _vnx_name)
	:	Module::Module(_vnx_name)
{
	vnx::read_config(vnx_name + ".input", input);
	vnx::read_config(vnx_name + ".address", address);
	vnx::read_config(vnx_name + ".port", port);
	vnx::read_config(vnx_name + ".stats_interval_ms", stats_interval_ms);
}

vnx::Hash64 UDP_SenderBase::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string UDP_SenderBase::get_type_name() const {
	return "pilot.base.UDP_Sender";
}

const vnx::TypeCode* UDP_SenderBase::get_type_code() const {
	return pilot::base::vnx_native_type_code_UDP_SenderBase;
}

void UDP_SenderBase::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = pilot::base::vnx_native_type_code_UDP_SenderBase;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, input);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, address);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, port);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, stats_interval_ms);
	_visitor.type_end(*_type_code);
}

void UDP_SenderBase::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"input\": "; vnx::write(_out, input);
	_out << ", \"address\": "; vnx::write(_out, address);
	_out << ", \"port\": "; vnx::write(_out, port);
	_out << ", \"stats_interval_ms\": "; vnx::write(_out, stats_interval_ms);
	_out << "}";
}

void UDP_SenderBase::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object UDP_SenderBase::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.UDP_Sender";
	_object["input"] = input;
	_object["address"] = address;
	_object["port"] = port;
	_object["stats_interval_ms"] = stats_interval_ms;
	return _object;
}

void UDP_SenderBase::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "address") {
			_entry.second.to(address);
		} else if(_entry.first == "input") {
			_entry.second.to(input);
		} else if(_entry.first == "port") {
			_entry.second.to(port);
		} else if(_entry.first == "stats_interval_ms") {
			_entry.second.to(stats_interval_ms);
		}
	}
}

vnx::Variant UDP_SenderBase::get_field(const std::string& _name) const {
	if(_name == "input") {
		return vnx::Variant(input);
	}
	if(_name == "address") {
		return vnx::Variant(address);
	}
	if(_name == "port") {
		return vnx::Variant(port);
	}
	if(_name == "stats_interval_ms") {
		return vnx::Variant(stats_interval_ms);
	}
	return vnx::Variant();
}

void UDP_SenderBase::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "input") {
		_value.to(input);
	} else if(_name == "address") {
		_value.to(address);
	} else if(_name == "port") {
		_value.to(port);
	} else if(_name == "stats_interval_ms") {
		_value.to(stats_interval_ms);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const UDP_SenderBase& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, UDP_SenderBase& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* UDP_SenderBase::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> UDP_SenderBase::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.UDP_Sender";
	type_code->type_hash = vnx::Hash64(0xdefb7c71f4bfa0a0ull);
	type_code->code_hash = vnx::Hash64(0x2012475c1d276238ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::pilot::base::UDP_SenderBase);
	type_code->methods.resize(9);
	type_code->methods[0] = ::vnx::ModuleInterface_vnx_get_config_object::static_get_type_code();
	type_code->methods[1] = ::vnx::ModuleInterface_vnx_get_config::static_get_type_code();
	type_code->methods[2] = ::vnx::ModuleInterface_vnx_set_config_object::static_get_type_code();
	type_code->methods[3] = ::vnx::ModuleInterface_vnx_set_config::static_get_type_code();
	type_code->methods[4] = ::vnx::ModuleInterface_vnx_get_type_code::static_get_type_code();
	type_code->methods[5] = ::vnx::ModuleInterface_vnx_get_module_info::static_get_type_code();
	type_code->methods[6] = ::vnx::ModuleInterface_vnx_restart::static_get_type_code();
	type_code->methods[7] = ::vnx::ModuleInterface_vnx_stop::static_get_type_code();
	type_code->methods[8] = ::vnx::ModuleInterface_vnx_self_test::static_get_type_code();
	type_code->fields.resize(4);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "input";
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[1];
		field.is_extended = true;
		field.name = "address";
		field.code = {32};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 4;
		field.name = "port";
		field.code = {7};
	}
	{
		auto& field = type_code->fields[3];
		field.data_size = 4;
		field.name = "stats_interval_ms";
		field.value = vnx::to_string(10000);
		field.code = {7};
	}
	type_code->build();
	return type_code;
}

void UDP_SenderBase::vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) {
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

std::shared_ptr<vnx::Value> UDP_SenderBase::vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) {
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
	}
	auto _ex = vnx::NoSuchMethod::create();
	_ex->dst_mac = vnx_request ? vnx_request->dst_mac : vnx::Hash64();
	_ex->method = _method->get_type_name();
	return _ex;
}


} // namespace pilot
} // namespace base


namespace vnx {

void read(TypeInput& in, ::pilot::base::UDP_SenderBase& value, const TypeCode* type_code, const uint16_t* code) {
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
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.port, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[3]) {
			vnx::read_value(_buf + _field->offset, value.stats_interval_ms, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.input, type_code, _field->code.data()); break;
			case 1: vnx::read(in, value.address, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::UDP_SenderBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::vnx_native_type_code_UDP_SenderBase;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::UDP_SenderBase>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(8);
	vnx::write_value(_buf + 0, value.port);
	vnx::write_value(_buf + 4, value.stats_interval_ms);
	vnx::write(out, value.input, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.address, type_code, type_code->fields[1].code.data());
}

void read(std::istream& in, ::pilot::base::UDP_SenderBase& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::UDP_SenderBase& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::UDP_SenderBase& value) {
	value.accept(visitor);
}

} // vnx
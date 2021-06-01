
// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/SerialPort_close_port.hxx>
#include <pilot/base/SerialPort_close_port_return.hxx>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace pilot {
namespace base {


const vnx::Hash64 SerialPort_close_port::VNX_TYPE_HASH(0x325a9542af22132full);
const vnx::Hash64 SerialPort_close_port::VNX_CODE_HASH(0xcaa93efea332564dull);

vnx::Hash64 SerialPort_close_port::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string SerialPort_close_port::get_type_name() const {
	return "pilot.base.SerialPort.close_port";
}

const vnx::TypeCode* SerialPort_close_port::get_type_code() const {
	return pilot::base::vnx_native_type_code_SerialPort_close_port;
}

std::shared_ptr<SerialPort_close_port> SerialPort_close_port::create() {
	return std::make_shared<SerialPort_close_port>();
}

std::shared_ptr<vnx::Value> SerialPort_close_port::clone() const {
	return std::make_shared<SerialPort_close_port>(*this);
}

void SerialPort_close_port::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void SerialPort_close_port::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void SerialPort_close_port::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = pilot::base::vnx_native_type_code_SerialPort_close_port;
	_visitor.type_begin(*_type_code);
	_visitor.type_end(*_type_code);
}

void SerialPort_close_port::write(std::ostream& _out) const {
	_out << "{\"__type\": \"pilot.base.SerialPort.close_port\"";
	_out << "}";
}

void SerialPort_close_port::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object SerialPort_close_port::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.SerialPort.close_port";
	return _object;
}

void SerialPort_close_port::from_object(const vnx::Object& _object) {
}

vnx::Variant SerialPort_close_port::get_field(const std::string& _name) const {
	return vnx::Variant();
}

void SerialPort_close_port::set_field(const std::string& _name, const vnx::Variant& _value) {
	throw std::logic_error("no such field: '" + _name + "'");
}

/// \private
std::ostream& operator<<(std::ostream& _out, const SerialPort_close_port& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, SerialPort_close_port& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* SerialPort_close_port::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> SerialPort_close_port::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.SerialPort.close_port";
	type_code->type_hash = vnx::Hash64(0x325a9542af22132full);
	type_code->code_hash = vnx::Hash64(0xcaa93efea332564dull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->is_method = true;
	type_code->native_size = sizeof(::pilot::base::SerialPort_close_port);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<SerialPort_close_port>(); };
	type_code->return_type = ::pilot::base::SerialPort_close_port_return::static_get_type_code();
	type_code->build();
	return type_code;
}


} // namespace pilot
} // namespace base


namespace vnx {

void read(TypeInput& in, ::pilot::base::SerialPort_close_port& value, const TypeCode* type_code, const uint16_t* code) {
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
	if(type_code->is_matched) {
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::SerialPort_close_port& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::vnx_native_type_code_SerialPort_close_port;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::SerialPort_close_port>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
}

void read(std::istream& in, ::pilot::base::SerialPort_close_port& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::SerialPort_close_port& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::SerialPort_close_port& value) {
	value.accept(visitor);
}

} // vnx

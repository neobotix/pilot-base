
// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/can_error_t.hxx>
#include <pilot/base/can_error_class_e.hxx>

#include <vnx/vnx.h>


namespace pilot {
namespace base {


const vnx::Hash64 can_error_t::VNX_TYPE_HASH(0x2739d295fa73821cull);
const vnx::Hash64 can_error_t::VNX_CODE_HASH(0x5bb5a1d6aef75cbbull);

vnx::Hash64 can_error_t::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string can_error_t::get_type_name() const {
	return "pilot.base.can_error_t";
}

const vnx::TypeCode* can_error_t::get_type_code() const {
	return pilot::base::vnx_native_type_code_can_error_t;
}

std::shared_ptr<can_error_t> can_error_t::create() {
	return std::make_shared<can_error_t>();
}

std::shared_ptr<can_error_t> can_error_t::clone() const {
	return std::make_shared<can_error_t>(*this);
}

void can_error_t::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void can_error_t::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void can_error_t::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = pilot::base::vnx_native_type_code_can_error_t;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, error_classes);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, num_tx_errors);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, num_rx_errors);
	_visitor.type_end(*_type_code);
}

void can_error_t::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"error_classes\": "; vnx::write(_out, error_classes);
	_out << ", \"num_tx_errors\": "; vnx::write(_out, num_tx_errors);
	_out << ", \"num_rx_errors\": "; vnx::write(_out, num_rx_errors);
	_out << "}";
}

void can_error_t::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object can_error_t::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.can_error_t";
	_object["error_classes"] = error_classes;
	_object["num_tx_errors"] = num_tx_errors;
	_object["num_rx_errors"] = num_rx_errors;
	return _object;
}

void can_error_t::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "error_classes") {
			_entry.second.to(error_classes);
		} else if(_entry.first == "num_rx_errors") {
			_entry.second.to(num_rx_errors);
		} else if(_entry.first == "num_tx_errors") {
			_entry.second.to(num_tx_errors);
		}
	}
}

vnx::Variant can_error_t::get_field(const std::string& _name) const {
	if(_name == "error_classes") {
		return vnx::Variant(error_classes);
	}
	if(_name == "num_tx_errors") {
		return vnx::Variant(num_tx_errors);
	}
	if(_name == "num_rx_errors") {
		return vnx::Variant(num_rx_errors);
	}
	return vnx::Variant();
}

void can_error_t::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "error_classes") {
		_value.to(error_classes);
	} else if(_name == "num_tx_errors") {
		_value.to(num_tx_errors);
	} else if(_name == "num_rx_errors") {
		_value.to(num_rx_errors);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const can_error_t& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, can_error_t& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* can_error_t::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> can_error_t::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.can_error_t";
	type_code->type_hash = vnx::Hash64(0x2739d295fa73821cull);
	type_code->code_hash = vnx::Hash64(0x5bb5a1d6aef75cbbull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::pilot::base::can_error_t);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<vnx::Struct<can_error_t>>(); };
	type_code->depends.resize(1);
	type_code->depends[0] = ::pilot::base::can_error_class_e::static_get_type_code();
	type_code->fields.resize(3);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "error_classes";
		field.code = {12, 19, 0};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 4;
		field.name = "num_tx_errors";
		field.value = vnx::to_string(0);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 4;
		field.name = "num_rx_errors";
		field.value = vnx::to_string(0);
		field.code = {3};
	}
	type_code->build();
	return type_code;
}


} // namespace pilot
} // namespace base


namespace vnx {

void read(TypeInput& in, ::pilot::base::can_error_t& value, const TypeCode* type_code, const uint16_t* code) {
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
			vnx::read_value(_buf + _field->offset, value.num_tx_errors, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.num_rx_errors, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.error_classes, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::can_error_t& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::vnx_native_type_code_can_error_t;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::can_error_t>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(8);
	vnx::write_value(_buf + 0, value.num_tx_errors);
	vnx::write_value(_buf + 4, value.num_rx_errors);
	vnx::write(out, value.error_classes, type_code, type_code->fields[0].code.data());
}

void read(std::istream& in, ::pilot::base::can_error_t& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::can_error_t& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::can_error_t& value) {
	value.accept(visitor);
}

bool is_equivalent<::pilot::base::can_error_t>::operator()(const uint16_t* code, const TypeCode* type_code) {
	if(code[0] != CODE_STRUCT || !type_code) {
		return false;
	}
	type_code = type_code->depends[code[1]];
	return type_code->type_hash == ::pilot::base::can_error_t::VNX_TYPE_HASH && type_code->is_equivalent;
}

} // vnx
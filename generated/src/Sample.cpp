
// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/Sample.hxx>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace pilot {
namespace base {


const vnx::Hash64 Sample::VNX_TYPE_HASH(0xde796e4da0f9430full);
const vnx::Hash64 Sample::VNX_CODE_HASH(0x230134e77979a1d8ull);

vnx::Hash64 Sample::get_type_hash() const {
	return VNX_TYPE_HASH;
}

const char* Sample::get_type_name() const {
	return "pilot.base.Sample";
}
const vnx::TypeCode* Sample::get_type_code() const {
	return pilot::base::vnx_native_type_code_Sample;
}

std::shared_ptr<Sample> Sample::create() {
	return std::make_shared<Sample>();
}

std::shared_ptr<vnx::Value> Sample::clone() const {
	return std::make_shared<Sample>(*this);
}

void Sample::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void Sample::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void Sample::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = pilot::base::vnx_native_type_code_Sample;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, time);
	_visitor.type_end(*_type_code);
}

void Sample::write(std::ostream& _out) const {
	_out << "{\"__type\": \"pilot.base.Sample\"";
	_out << ", \"time\": "; vnx::write(_out, time);
	_out << "}";
}

void Sample::read(std::istream& _in) {
	std::map<std::string, std::string> _object;
	vnx::read_object(_in, _object);
	for(const auto& _entry : _object) {
		if(_entry.first == "time") {
			vnx::from_string(_entry.second, time);
		}
	}
}

vnx::Object Sample::to_object() const {
	vnx::Object _object;
	_object["__type"] = "pilot.base.Sample";
	_object["time"] = time;
	return _object;
}

void Sample::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "time") {
			_entry.second.to(time);
		}
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const Sample& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, Sample& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* Sample::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> Sample::static_create_type_code() {
	std::shared_ptr<vnx::TypeCode> type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "pilot.base.Sample";
	type_code->type_hash = vnx::Hash64(0xde796e4da0f9430full);
	type_code->code_hash = vnx::Hash64(0x230134e77979a1d8ull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<Sample>(); };
	type_code->fields.resize(1);
	{
		vnx::TypeField& field = type_code->fields[0];
		field.name = "time";
		field.code = {8};
	}
	type_code->build();
	return type_code;
}


} // namespace pilot
} // namespace base


namespace vnx {

void read(TypeInput& in, ::pilot::base::Sample& value, const TypeCode* type_code, const uint16_t* code) {
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
		throw std::logic_error("read(): type_code == 0");
	}
	if(code) {
		switch(code[0]) {
			case CODE_STRUCT: type_code = type_code->depends[code[1]]; break;
			case CODE_ALT_STRUCT: type_code = type_code->depends[vnx::flip_bytes(code[1])]; break;
			default: vnx::skip(in, type_code, code); return;
		}
	}
	const char* const _buf = in.read(type_code->total_field_size);
	if(type_code->is_matched) {
		{
			const vnx::TypeField* const _field = type_code->field_map[0];
			if(_field) {
				vnx::read_value(_buf + _field->offset, value.time, _field->code.data());
			}
		}
	}
	for(const vnx::TypeField* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::pilot::base::Sample& value, const TypeCode* type_code, const uint16_t* code) {
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = pilot::base::vnx_native_type_code_Sample;
		out.write_type_code(type_code);
		vnx::write_class_header<::pilot::base::Sample>(out);
	}
	if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(8);
	vnx::write_value(_buf + 0, value.time);
}

void read(std::istream& in, ::pilot::base::Sample& value) {
	value.read(in);
}

void write(std::ostream& out, const ::pilot::base::Sample& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::pilot::base::Sample& value) {
	value.accept(visitor);
}

} // vnx

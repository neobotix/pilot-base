
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_SerialPort_open_port_HXX_
#define INCLUDE_pilot_base_SerialPort_open_port_HXX_

#include <pilot/base/package.hxx>
#include <vnx/Value.h>


namespace pilot {
namespace base {

class SerialPort_open_port : public ::vnx::Value {
public:
	
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	vnx::Hash64 get_type_hash() const override;
	const char* get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<SerialPort_open_port> create();
	std::shared_ptr<vnx::Value> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	vnx::Variant get_field(const std::string& name) const;
	void set_field(const std::string& name, const vnx::Variant& value);
	
	friend std::ostream& operator<<(std::ostream& _out, const SerialPort_open_port& _value);
	friend std::istream& operator>>(std::istream& _in, SerialPort_open_port& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace pilot
} // namespace base

#endif // INCLUDE_pilot_base_SerialPort_open_port_HXX_

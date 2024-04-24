
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_in_address_t_HXX_
#define INCLUDE_pilot_base_in_address_t_HXX_

#include <vnx/Type.h>
#include <pilot/base/package.hxx>


namespace pilot {
namespace base {

struct in_address_t {
	
	
	std::string address;
	int32_t port = 0;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xf0ba186b6082b1d2ull;
	
	in_address_t() {}
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	static std::shared_ptr<in_address_t> create();
	std::shared_ptr<in_address_t> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	vnx::Variant get_field(const std::string& name) const;
	void set_field(const std::string& name, const vnx::Variant& value);
	
	friend std::ostream& operator<<(std::ostream& _out, const in_address_t& _value);
	friend std::istream& operator>>(std::istream& _in, in_address_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace pilot
} // namespace base


namespace vnx {

template<>
struct is_equivalent<::pilot::base::in_address_t> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_pilot_base_in_address_t_HXX_

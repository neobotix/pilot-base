
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_canopen_nmt_command_e_HXX_
#define INCLUDE_pilot_base_canopen_nmt_command_e_HXX_

#include <vnx/Type.h>
#include <pilot/base/canopen/package.hxx>


namespace pilot {
namespace base {
namespace canopen {

struct nmt_command_e {
	
	enum enum_t : uint32_t {
		GO_TO_OPERATIONAL = 2221976813l,
		GO_TO_PRE_OPERATIONAL = 269874636l,
		GO_TO_RESET_COMMUNICATION = 2167780285l,
		GO_TO_RESET_NODE = 3845696215l,
		GO_TO_STOPPED = 2689154386l,
	};
	
	::pilot::base::canopen::nmt_command_e::enum_t value = ::pilot::base::canopen::nmt_command_e::enum_t(0);
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xbf49909e851a6027ull;
	
	nmt_command_e() {}
	
	nmt_command_e(const enum_t& _value) { value = _value; }
	nmt_command_e(const ::pilot::base::canopen::nmt_command_e& _other) { value = _other.value; }
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	operator enum_t() const { return value; }
	nmt_command_e& operator=(const enum_t& _value) { value = _value; return *this; }
	nmt_command_e& operator=(const ::pilot::base::canopen::nmt_command_e& _other) { value = _other.value; return *this; }
	
	static std::shared_ptr<nmt_command_e> create();
	std::shared_ptr<nmt_command_e> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::bool_t is_valid() const;
	std::string to_string() const;
	std::string to_string_value() const;
	std::string to_string_value_full() const;
	
	void from_string(const std::string& str);
	void from_string_value(const std::string& name);
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	vnx::Variant get_field(const std::string& name) const;
	void set_field(const std::string& name, const vnx::Variant& value);
	
	friend std::ostream& operator<<(std::ostream& _out, const nmt_command_e& _value);
	friend std::istream& operator>>(std::istream& _in, nmt_command_e& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace pilot
} // namespace base
} // namespace canopen


namespace vnx {

void read(TypeInput& in, ::pilot::base::canopen::nmt_command_e::enum_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private

void write(TypeOutput& out, const ::pilot::base::canopen::nmt_command_e::enum_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private

template<>
std::string to_string(const ::pilot::base::canopen::nmt_command_e& _value); ///< \private

template<>
std::string to_string_value(const ::pilot::base::canopen::nmt_command_e& _value); ///< \private

template<>
std::string to_string_value_full(const ::pilot::base::canopen::nmt_command_e& _value); ///< \private

template<>
std::string to_string(const ::pilot::base::canopen::nmt_command_e::enum_t& _value); ///< \private

template<>
std::string to_string_value(const ::pilot::base::canopen::nmt_command_e::enum_t& _value); ///< \private

template<>
std::string to_string_value_full(const ::pilot::base::canopen::nmt_command_e::enum_t& _value); ///< \private

template<>
struct is_equivalent<::pilot::base::canopen::nmt_command_e> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_pilot_base_canopen_nmt_command_e_HXX_
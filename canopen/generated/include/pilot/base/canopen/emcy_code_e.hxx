
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_canopen_emcy_code_e_HXX_
#define INCLUDE_pilot_base_canopen_emcy_code_e_HXX_

#include <vnx/Type.h>
#include <pilot/base/canopen/package.hxx>


namespace pilot {
namespace base {
namespace canopen {

struct emcy_code_e {
	
	enum enum_t : uint32_t {
		ADDITIONAL_FUNCTIONS = 2521423643l,
		ADDITIONAL_MODULES = 583241226l,
		CAN_ERROR_PASSIVE = 2504912088l,
		CAN_ID_COLLISION = 2986669073l,
		CAN_OVERRUN = 1071682401l,
		CAN_RECOVERED = 2306010892l,
		COMMUNICATION = 487288233l,
		CURRENT = 2853934165l,
		CURRENT_INPUT = 2582093355l,
		CURRENT_INSIDE = 513425947l,
		CURRENT_OUTPUT = 1254426932l,
		DAM_MPDO_NOT_PROCESSED = 506174374l,
		DATA_SET = 4276352321l,
		DEVICE_SPECIFIC = 3766952636l,
		EXTERNAL_ERROR = 616254643l,
		GENERIC_ERROR = 3059157402l,
		HARDWARE = 3520157551l,
		HEARTBEAT_ERROR = 3354804095l,
		INTERNAL_SOFTWARE = 3976734154l,
		MONITORING = 416611857l,
		NO_ERROR = 134115394l,
		PDO_LENGTH_ERROR = 1226538660l,
		PDO_LENGTH_EXCEEDED = 722766574l,
		PROTOCOL_ERROR = 1346031774l,
		RPDO_TIMEOUT = 3265130901l,
		SOFTWARE = 2410844169l,
		TEMPERATURE = 2506210592l,
		TEMPERATURE_AMBIENT = 3976088382l,
		TEMPERATURE_DEVICE = 2264987537l,
		UNEXPECTED_SYNC_LENGTH = 1608562062l,
		USER_SOFTWARE = 1994157918l,
		VOLTAGE = 1650878572l,
		VOLTAGE_INSIDE = 707070561l,
		VOLTAGE_MAINS = 2819794729l,
		VOLTAGE_OUTPUT = 2121941326l,
	};
	
	::pilot::base::canopen::emcy_code_e::enum_t value = ::pilot::base::canopen::emcy_code_e::enum_t(0);
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xc0297cb989826ca8ull;
	
	emcy_code_e() {}
	
	emcy_code_e(const enum_t& _value) { value = _value; }
	emcy_code_e(const ::pilot::base::canopen::emcy_code_e& _other) { value = _other.value; }
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	operator enum_t() const { return value; }
	emcy_code_e& operator=(const enum_t& _value) { value = _value; return *this; }
	emcy_code_e& operator=(const ::pilot::base::canopen::emcy_code_e& _other) { value = _other.value; return *this; }
	
	static std::shared_ptr<emcy_code_e> create();
	std::shared_ptr<emcy_code_e> clone() const;
	
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
	
	friend std::ostream& operator<<(std::ostream& _out, const emcy_code_e& _value);
	friend std::istream& operator>>(std::istream& _in, emcy_code_e& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace pilot
} // namespace base
} // namespace canopen


namespace vnx {

void read(TypeInput& in, ::pilot::base::canopen::emcy_code_e::enum_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private

void write(TypeOutput& out, const ::pilot::base::canopen::emcy_code_e::enum_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private

template<>
std::string to_string(const ::pilot::base::canopen::emcy_code_e& _value); ///< \private

template<>
std::string to_string_value(const ::pilot::base::canopen::emcy_code_e& _value); ///< \private

template<>
std::string to_string_value_full(const ::pilot::base::canopen::emcy_code_e& _value); ///< \private

template<>
std::string to_string(const ::pilot::base::canopen::emcy_code_e::enum_t& _value); ///< \private

template<>
std::string to_string_value(const ::pilot::base::canopen::emcy_code_e::enum_t& _value); ///< \private

template<>
std::string to_string_value_full(const ::pilot::base::canopen::emcy_code_e::enum_t& _value); ///< \private

template<>
struct is_equivalent<::pilot::base::canopen::emcy_code_e> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_pilot_base_canopen_emcy_code_e_HXX_

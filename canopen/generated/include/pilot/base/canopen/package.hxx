
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_canopen_PACKAGE_HXX_
#define INCLUDE_pilot_base_canopen_PACKAGE_HXX_

#include <vnx/Type.h>

#include <pilot/base/package.hxx>
#include <vnx/package.hxx>


namespace pilot {
namespace base {
namespace canopen {


struct emcy_code_e;
struct emcy_register_e;
struct nmt_command_e;
struct nmt_state_e;
struct node_t;
struct sdo_ccs_e;
struct sdo_error_e;
struct sdo_scs_e;

extern const vnx::TypeCode* const vnx_native_type_code_emcy_code_e; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_emcy_register_e; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_nmt_command_e; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_nmt_state_e; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_node_t; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_sdo_ccs_e; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_sdo_error_e; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_sdo_scs_e; ///< \private

} // namespace pilot
} // namespace base
} // namespace canopen


namespace vnx {

void read(TypeInput& in, ::pilot::base::canopen::emcy_code_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::canopen::emcy_register_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::canopen::nmt_command_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::canopen::nmt_state_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::canopen::node_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::canopen::sdo_ccs_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::canopen::sdo_error_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::canopen::sdo_scs_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private

void write(TypeOutput& out, const ::pilot::base::canopen::emcy_code_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::canopen::emcy_register_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::canopen::nmt_command_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::canopen::nmt_state_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::canopen::node_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::canopen::sdo_ccs_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::canopen::sdo_error_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::canopen::sdo_scs_e& value, const TypeCode* type_code, const uint16_t* code); ///< \private

void read(std::istream& in, ::pilot::base::canopen::emcy_code_e& value); ///< \private
void read(std::istream& in, ::pilot::base::canopen::emcy_register_e& value); ///< \private
void read(std::istream& in, ::pilot::base::canopen::nmt_command_e& value); ///< \private
void read(std::istream& in, ::pilot::base::canopen::nmt_state_e& value); ///< \private
void read(std::istream& in, ::pilot::base::canopen::node_t& value); ///< \private
void read(std::istream& in, ::pilot::base::canopen::sdo_ccs_e& value); ///< \private
void read(std::istream& in, ::pilot::base::canopen::sdo_error_e& value); ///< \private
void read(std::istream& in, ::pilot::base::canopen::sdo_scs_e& value); ///< \private

void write(std::ostream& out, const ::pilot::base::canopen::emcy_code_e& value); ///< \private
void write(std::ostream& out, const ::pilot::base::canopen::emcy_register_e& value); ///< \private
void write(std::ostream& out, const ::pilot::base::canopen::nmt_command_e& value); ///< \private
void write(std::ostream& out, const ::pilot::base::canopen::nmt_state_e& value); ///< \private
void write(std::ostream& out, const ::pilot::base::canopen::node_t& value); ///< \private
void write(std::ostream& out, const ::pilot::base::canopen::sdo_ccs_e& value); ///< \private
void write(std::ostream& out, const ::pilot::base::canopen::sdo_error_e& value); ///< \private
void write(std::ostream& out, const ::pilot::base::canopen::sdo_scs_e& value); ///< \private

void accept(Visitor& visitor, const ::pilot::base::canopen::emcy_code_e& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::canopen::emcy_register_e& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::canopen::nmt_command_e& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::canopen::nmt_state_e& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::canopen::node_t& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::canopen::sdo_ccs_e& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::canopen::sdo_error_e& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::canopen::sdo_scs_e& value); ///< \private

/// \private
template<>
struct type<::pilot::base::canopen::emcy_code_e> {
	void read(TypeInput& in, ::pilot::base::canopen::emcy_code_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::emcy_code_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::emcy_code_e& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::emcy_code_e& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::emcy_code_e& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::emcy_code_e& value, bool special = false);
};

/// \private
template<>
struct type<::pilot::base::canopen::emcy_register_e> {
	void read(TypeInput& in, ::pilot::base::canopen::emcy_register_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::emcy_register_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::emcy_register_e& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::emcy_register_e& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::emcy_register_e& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::emcy_register_e& value, bool special = false);
};

/// \private
template<>
struct type<::pilot::base::canopen::nmt_command_e> {
	void read(TypeInput& in, ::pilot::base::canopen::nmt_command_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::nmt_command_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::nmt_command_e& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::nmt_command_e& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::nmt_command_e& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::nmt_command_e& value, bool special = false);
};

/// \private
template<>
struct type<::pilot::base::canopen::nmt_state_e> {
	void read(TypeInput& in, ::pilot::base::canopen::nmt_state_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::nmt_state_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::nmt_state_e& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::nmt_state_e& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::nmt_state_e& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::nmt_state_e& value, bool special = false);
};

/// \private
template<>
struct type<::pilot::base::canopen::node_t> {
	void read(TypeInput& in, ::pilot::base::canopen::node_t& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::node_t& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::node_t& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::node_t& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::node_t& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::node_t& value, bool special = false);
};

/// \private
template<>
struct type<::pilot::base::canopen::sdo_ccs_e> {
	void read(TypeInput& in, ::pilot::base::canopen::sdo_ccs_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::sdo_ccs_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::sdo_ccs_e& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::sdo_ccs_e& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::sdo_ccs_e& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::sdo_ccs_e& value, bool special = false);
};

/// \private
template<>
struct type<::pilot::base::canopen::sdo_error_e> {
	void read(TypeInput& in, ::pilot::base::canopen::sdo_error_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::sdo_error_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::sdo_error_e& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::sdo_error_e& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::sdo_error_e& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::sdo_error_e& value, bool special = false);
};

/// \private
template<>
struct type<::pilot::base::canopen::sdo_scs_e> {
	void read(TypeInput& in, ::pilot::base::canopen::sdo_scs_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::canopen::sdo_scs_e& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::canopen::sdo_scs_e& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::canopen::sdo_scs_e& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::canopen::sdo_scs_e& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code);
	void create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::canopen::sdo_scs_e& value, bool special = false);
};


} // namespace vnx

#endif // INCLUDE_pilot_base_canopen_PACKAGE_HXX_


// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_PACKAGE_HXX_
#define INCLUDE_pilot_base_PACKAGE_HXX_

#include <vnx/Type.h>

#include <vnx/package.hxx>


namespace pilot {
namespace base {


class CAN_Frame;
class CAN_ProxyBase;
class DataPacket;
class JoyData;
class JoystickBase;
class Joystick_close_device;
class Joystick_close_device_return;
class Joystick_open_device;
class Joystick_open_device_return;
class Sample;
class SerialPortBase;
class SerialPort_close_port;
class SerialPort_close_port_return;
class SerialPort_open_port;
class SerialPort_open_port_return;
class SocketSignal;
class UDP_ReceiverBase;
class UDP_Receiver_close_port;
class UDP_Receiver_close_port_return;
class UDP_Receiver_open_port;
class UDP_Receiver_open_port_return;

extern const vnx::TypeCode* const vnx_native_type_code_CAN_Frame; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_CAN_ProxyBase; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_DataPacket; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_JoyData; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_JoystickBase; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_Joystick_close_device; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_Joystick_close_device_return; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_Joystick_open_device; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_Joystick_open_device_return; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_Sample; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_SerialPortBase; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_SerialPort_close_port; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_SerialPort_close_port_return; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_SerialPort_open_port; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_SerialPort_open_port_return; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_SocketSignal; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_UDP_ReceiverBase; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_UDP_Receiver_close_port; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_UDP_Receiver_close_port_return; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_UDP_Receiver_open_port; ///< \private
extern const vnx::TypeCode* const vnx_native_type_code_UDP_Receiver_open_port_return; ///< \private

} // namespace pilot
} // namespace base


namespace vnx {

void read(TypeInput& in, ::pilot::base::CAN_Frame& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::CAN_ProxyBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::DataPacket& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::JoyData& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::JoystickBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::Joystick_close_device& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::Joystick_close_device_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::Joystick_open_device& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::Joystick_open_device_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::Sample& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::SerialPortBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::SerialPort_close_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::SerialPort_close_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::SerialPort_open_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::SerialPort_open_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::SocketSignal& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::UDP_ReceiverBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::UDP_Receiver_close_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::UDP_Receiver_close_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::UDP_Receiver_open_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void read(TypeInput& in, ::pilot::base::UDP_Receiver_open_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private

void write(TypeOutput& out, const ::pilot::base::CAN_Frame& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::CAN_ProxyBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::DataPacket& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::JoyData& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::JoystickBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::Joystick_close_device& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::Joystick_close_device_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::Joystick_open_device& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::Joystick_open_device_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::Sample& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::SerialPortBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::SerialPort_close_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::SerialPort_close_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::SerialPort_open_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::SerialPort_open_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::SocketSignal& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::UDP_ReceiverBase& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_close_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_close_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_open_port& value, const TypeCode* type_code, const uint16_t* code); ///< \private
void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_open_port_return& value, const TypeCode* type_code, const uint16_t* code); ///< \private

void read(std::istream& in, ::pilot::base::CAN_Frame& value); ///< \private
void read(std::istream& in, ::pilot::base::CAN_ProxyBase& value); ///< \private
void read(std::istream& in, ::pilot::base::DataPacket& value); ///< \private
void read(std::istream& in, ::pilot::base::JoyData& value); ///< \private
void read(std::istream& in, ::pilot::base::JoystickBase& value); ///< \private
void read(std::istream& in, ::pilot::base::Joystick_close_device& value); ///< \private
void read(std::istream& in, ::pilot::base::Joystick_close_device_return& value); ///< \private
void read(std::istream& in, ::pilot::base::Joystick_open_device& value); ///< \private
void read(std::istream& in, ::pilot::base::Joystick_open_device_return& value); ///< \private
void read(std::istream& in, ::pilot::base::Sample& value); ///< \private
void read(std::istream& in, ::pilot::base::SerialPortBase& value); ///< \private
void read(std::istream& in, ::pilot::base::SerialPort_close_port& value); ///< \private
void read(std::istream& in, ::pilot::base::SerialPort_close_port_return& value); ///< \private
void read(std::istream& in, ::pilot::base::SerialPort_open_port& value); ///< \private
void read(std::istream& in, ::pilot::base::SerialPort_open_port_return& value); ///< \private
void read(std::istream& in, ::pilot::base::SocketSignal& value); ///< \private
void read(std::istream& in, ::pilot::base::UDP_ReceiverBase& value); ///< \private
void read(std::istream& in, ::pilot::base::UDP_Receiver_close_port& value); ///< \private
void read(std::istream& in, ::pilot::base::UDP_Receiver_close_port_return& value); ///< \private
void read(std::istream& in, ::pilot::base::UDP_Receiver_open_port& value); ///< \private
void read(std::istream& in, ::pilot::base::UDP_Receiver_open_port_return& value); ///< \private

void write(std::ostream& out, const ::pilot::base::CAN_Frame& value); ///< \private
void write(std::ostream& out, const ::pilot::base::CAN_ProxyBase& value); ///< \private
void write(std::ostream& out, const ::pilot::base::DataPacket& value); ///< \private
void write(std::ostream& out, const ::pilot::base::JoyData& value); ///< \private
void write(std::ostream& out, const ::pilot::base::JoystickBase& value); ///< \private
void write(std::ostream& out, const ::pilot::base::Joystick_close_device& value); ///< \private
void write(std::ostream& out, const ::pilot::base::Joystick_close_device_return& value); ///< \private
void write(std::ostream& out, const ::pilot::base::Joystick_open_device& value); ///< \private
void write(std::ostream& out, const ::pilot::base::Joystick_open_device_return& value); ///< \private
void write(std::ostream& out, const ::pilot::base::Sample& value); ///< \private
void write(std::ostream& out, const ::pilot::base::SerialPortBase& value); ///< \private
void write(std::ostream& out, const ::pilot::base::SerialPort_close_port& value); ///< \private
void write(std::ostream& out, const ::pilot::base::SerialPort_close_port_return& value); ///< \private
void write(std::ostream& out, const ::pilot::base::SerialPort_open_port& value); ///< \private
void write(std::ostream& out, const ::pilot::base::SerialPort_open_port_return& value); ///< \private
void write(std::ostream& out, const ::pilot::base::SocketSignal& value); ///< \private
void write(std::ostream& out, const ::pilot::base::UDP_ReceiverBase& value); ///< \private
void write(std::ostream& out, const ::pilot::base::UDP_Receiver_close_port& value); ///< \private
void write(std::ostream& out, const ::pilot::base::UDP_Receiver_close_port_return& value); ///< \private
void write(std::ostream& out, const ::pilot::base::UDP_Receiver_open_port& value); ///< \private
void write(std::ostream& out, const ::pilot::base::UDP_Receiver_open_port_return& value); ///< \private

void accept(Visitor& visitor, const ::pilot::base::CAN_Frame& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::CAN_ProxyBase& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::DataPacket& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::JoyData& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::JoystickBase& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::Joystick_close_device& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::Joystick_close_device_return& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::Joystick_open_device& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::Joystick_open_device_return& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::Sample& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::SerialPortBase& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::SerialPort_close_port& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::SerialPort_close_port_return& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::SerialPort_open_port& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::SerialPort_open_port_return& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::SocketSignal& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::UDP_ReceiverBase& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_close_port& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_close_port_return& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_open_port& value); ///< \private
void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_open_port_return& value); ///< \private

/// \private
template<>
struct type<::pilot::base::CAN_Frame> {
	void read(TypeInput& in, ::pilot::base::CAN_Frame& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::CAN_Frame& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::CAN_Frame& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::CAN_Frame& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::CAN_Frame& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::CAN_ProxyBase> {
	void read(TypeInput& in, ::pilot::base::CAN_ProxyBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::CAN_ProxyBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::CAN_ProxyBase& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::CAN_ProxyBase& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::CAN_ProxyBase& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::DataPacket> {
	void read(TypeInput& in, ::pilot::base::DataPacket& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::DataPacket& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::DataPacket& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::DataPacket& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::DataPacket& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::JoyData> {
	void read(TypeInput& in, ::pilot::base::JoyData& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::JoyData& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::JoyData& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::JoyData& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::JoyData& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::JoystickBase> {
	void read(TypeInput& in, ::pilot::base::JoystickBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::JoystickBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::JoystickBase& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::JoystickBase& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::JoystickBase& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::Joystick_close_device> {
	void read(TypeInput& in, ::pilot::base::Joystick_close_device& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::Joystick_close_device& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::Joystick_close_device& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::Joystick_close_device& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::Joystick_close_device& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::Joystick_close_device_return> {
	void read(TypeInput& in, ::pilot::base::Joystick_close_device_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::Joystick_close_device_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::Joystick_close_device_return& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::Joystick_close_device_return& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::Joystick_close_device_return& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::Joystick_open_device> {
	void read(TypeInput& in, ::pilot::base::Joystick_open_device& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::Joystick_open_device& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::Joystick_open_device& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::Joystick_open_device& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::Joystick_open_device& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::Joystick_open_device_return> {
	void read(TypeInput& in, ::pilot::base::Joystick_open_device_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::Joystick_open_device_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::Joystick_open_device_return& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::Joystick_open_device_return& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::Joystick_open_device_return& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::Sample> {
	void read(TypeInput& in, ::pilot::base::Sample& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::Sample& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::Sample& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::Sample& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::Sample& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::SerialPortBase> {
	void read(TypeInput& in, ::pilot::base::SerialPortBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::SerialPortBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::SerialPortBase& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::SerialPortBase& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::SerialPortBase& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::SerialPort_close_port> {
	void read(TypeInput& in, ::pilot::base::SerialPort_close_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::SerialPort_close_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::SerialPort_close_port& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::SerialPort_close_port& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::SerialPort_close_port& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::SerialPort_close_port_return> {
	void read(TypeInput& in, ::pilot::base::SerialPort_close_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::SerialPort_close_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::SerialPort_close_port_return& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::SerialPort_close_port_return& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::SerialPort_close_port_return& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::SerialPort_open_port> {
	void read(TypeInput& in, ::pilot::base::SerialPort_open_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::SerialPort_open_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::SerialPort_open_port& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::SerialPort_open_port& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::SerialPort_open_port& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::SerialPort_open_port_return> {
	void read(TypeInput& in, ::pilot::base::SerialPort_open_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::SerialPort_open_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::SerialPort_open_port_return& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::SerialPort_open_port_return& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::SerialPort_open_port_return& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::SocketSignal> {
	void read(TypeInput& in, ::pilot::base::SocketSignal& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::SocketSignal& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::SocketSignal& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::SocketSignal& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::SocketSignal& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::UDP_ReceiverBase> {
	void read(TypeInput& in, ::pilot::base::UDP_ReceiverBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::UDP_ReceiverBase& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::UDP_ReceiverBase& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::UDP_ReceiverBase& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::UDP_ReceiverBase& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::UDP_Receiver_close_port> {
	void read(TypeInput& in, ::pilot::base::UDP_Receiver_close_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_close_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::UDP_Receiver_close_port& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::UDP_Receiver_close_port& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_close_port& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::UDP_Receiver_close_port_return> {
	void read(TypeInput& in, ::pilot::base::UDP_Receiver_close_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_close_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::UDP_Receiver_close_port_return& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::UDP_Receiver_close_port_return& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_close_port_return& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::UDP_Receiver_open_port> {
	void read(TypeInput& in, ::pilot::base::UDP_Receiver_open_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_open_port& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::UDP_Receiver_open_port& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::UDP_Receiver_open_port& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_open_port& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};

/// \private
template<>
struct type<::pilot::base::UDP_Receiver_open_port_return> {
	void read(TypeInput& in, ::pilot::base::UDP_Receiver_open_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::read(in, value, type_code, code);
	}
	void write(TypeOutput& out, const ::pilot::base::UDP_Receiver_open_port_return& value, const TypeCode* type_code, const uint16_t* code) {
		vnx::write(out, value, type_code, code);
	}
	void read(std::istream& in, ::pilot::base::UDP_Receiver_open_port_return& value) {
		vnx::read(in, value);
	}
	void write(std::ostream& out, const ::pilot::base::UDP_Receiver_open_port_return& value) {
		vnx::write(out, value);
	}
	void accept(Visitor& visitor, const ::pilot::base::UDP_Receiver_open_port_return& value) {
		vnx::accept(visitor, value);
	}
	void create_dynamic_code(std::vector<uint16_t>& code) {
		code.push_back(CODE_ANY);
	}
};


} // namespace vnx

#endif // INCLUDE_pilot_base_PACKAGE_HXX_

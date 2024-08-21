
// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/CAN_Frame.hxx>
#include <pilot/base/CAN_ProxyBase.hxx>
#include <pilot/base/CAN_Proxy_send.hxx>
#include <pilot/base/CAN_Proxy_send_return.hxx>
#include <pilot/base/DataPacket.hxx>
#include <pilot/base/NetworkStreamBase.hxx>
#include <pilot/base/NetworkStream_connect.hxx>
#include <pilot/base/NetworkStream_connect_return.hxx>
#include <pilot/base/NetworkStream_disconnect.hxx>
#include <pilot/base/NetworkStream_disconnect_return.hxx>
#include <pilot/base/NetworkStream_is_connected.hxx>
#include <pilot/base/NetworkStream_is_connected_return.hxx>
#include <pilot/base/SerialPortBase.hxx>
#include <pilot/base/SerialPort_close_port.hxx>
#include <pilot/base/SerialPort_close_port_return.hxx>
#include <pilot/base/SerialPort_open_port.hxx>
#include <pilot/base/SerialPort_open_port_return.hxx>
#include <pilot/base/SocketSignal.hxx>
#include <pilot/base/UDP_SocketBase.hxx>
#include <pilot/base/can_adapter_e.hxx>
#include <pilot/base/can_error_class_e.hxx>
#include <pilot/base/can_error_t.hxx>
#include <pilot/base/in_address_t.hxx>
#include <pilot/base/socketcan_options_t.hxx>

#include <pilot/base/package.hxx>
#include <vnx/vnx.h>



namespace vnx {

void type<::pilot::base::CAN_Frame>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::CAN_Frame());
}

void type<::pilot::base::CAN_Frame>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::CAN_Frame& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::CAN_Proxy_send>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::CAN_Proxy_send());
}

void type<::pilot::base::CAN_Proxy_send>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::CAN_Proxy_send& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::CAN_Proxy_send_return>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::CAN_Proxy_send_return());
}

void type<::pilot::base::CAN_Proxy_send_return>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::CAN_Proxy_send_return& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::DataPacket>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::DataPacket());
}

void type<::pilot::base::DataPacket>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::DataPacket& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::NetworkStream_connect>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::NetworkStream_connect());
}

void type<::pilot::base::NetworkStream_connect>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::NetworkStream_connect& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::NetworkStream_connect_return>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::NetworkStream_connect_return());
}

void type<::pilot::base::NetworkStream_connect_return>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::NetworkStream_connect_return& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::NetworkStream_disconnect>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::NetworkStream_disconnect());
}

void type<::pilot::base::NetworkStream_disconnect>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::NetworkStream_disconnect& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::NetworkStream_disconnect_return>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::NetworkStream_disconnect_return());
}

void type<::pilot::base::NetworkStream_disconnect_return>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::NetworkStream_disconnect_return& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::NetworkStream_is_connected>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::NetworkStream_is_connected());
}

void type<::pilot::base::NetworkStream_is_connected>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::NetworkStream_is_connected& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::NetworkStream_is_connected_return>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::NetworkStream_is_connected_return());
}

void type<::pilot::base::NetworkStream_is_connected_return>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::NetworkStream_is_connected_return& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::SerialPort_close_port>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::SerialPort_close_port());
}

void type<::pilot::base::SerialPort_close_port>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::SerialPort_close_port& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::SerialPort_close_port_return>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::SerialPort_close_port_return());
}

void type<::pilot::base::SerialPort_close_port_return>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::SerialPort_close_port_return& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::SerialPort_open_port>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::SerialPort_open_port());
}

void type<::pilot::base::SerialPort_open_port>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::SerialPort_open_port& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::SerialPort_open_port_return>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::SerialPort_open_port_return());
}

void type<::pilot::base::SerialPort_open_port_return>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::SerialPort_open_port_return& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::SocketSignal>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::SocketSignal());
}

void type<::pilot::base::SocketSignal>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::SocketSignal& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::can_adapter_e>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::can_adapter_e());
}

void type<::pilot::base::can_adapter_e>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::can_adapter_e& value, bool special) {
	if(!special || value.is_valid()) {
		code.push_back(CODE_STRING);
	} else {
		code.push_back(CODE_UINT32);
	}
}

void type<::pilot::base::can_error_class_e>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::can_error_class_e());
}

void type<::pilot::base::can_error_class_e>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::can_error_class_e& value, bool special) {
	if(!special || value.is_valid()) {
		code.push_back(CODE_STRING);
	} else {
		code.push_back(CODE_UINT32);
	}
}

void type<::pilot::base::can_error_t>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::can_error_t());
}

void type<::pilot::base::can_error_t>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::can_error_t& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::in_address_t>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::in_address_t());
}

void type<::pilot::base::in_address_t>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::in_address_t& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::pilot::base::socketcan_options_t>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::pilot::base::socketcan_options_t());
}

void type<::pilot::base::socketcan_options_t>::create_dynamic_code(std::vector<uint16_t>& code, const ::pilot::base::socketcan_options_t& value, bool special) {
	code.push_back(CODE_OBJECT);
}


} // namespace vnx


namespace pilot {
namespace base {


static void register_all_types() {
	vnx::register_type_code(::pilot::base::CAN_Frame::static_create_type_code());
	vnx::register_type_code(::pilot::base::CAN_ProxyBase::static_create_type_code());
	vnx::register_type_code(::pilot::base::CAN_Proxy_send::static_create_type_code());
	vnx::register_type_code(::pilot::base::CAN_Proxy_send_return::static_create_type_code());
	vnx::register_type_code(::pilot::base::DataPacket::static_create_type_code());
	vnx::register_type_code(::pilot::base::NetworkStreamBase::static_create_type_code());
	vnx::register_type_code(::pilot::base::NetworkStream_connect::static_create_type_code());
	vnx::register_type_code(::pilot::base::NetworkStream_connect_return::static_create_type_code());
	vnx::register_type_code(::pilot::base::NetworkStream_disconnect::static_create_type_code());
	vnx::register_type_code(::pilot::base::NetworkStream_disconnect_return::static_create_type_code());
	vnx::register_type_code(::pilot::base::NetworkStream_is_connected::static_create_type_code());
	vnx::register_type_code(::pilot::base::NetworkStream_is_connected_return::static_create_type_code());
	vnx::register_type_code(::pilot::base::SerialPortBase::static_create_type_code());
	vnx::register_type_code(::pilot::base::SerialPort_close_port::static_create_type_code());
	vnx::register_type_code(::pilot::base::SerialPort_close_port_return::static_create_type_code());
	vnx::register_type_code(::pilot::base::SerialPort_open_port::static_create_type_code());
	vnx::register_type_code(::pilot::base::SerialPort_open_port_return::static_create_type_code());
	vnx::register_type_code(::pilot::base::SocketSignal::static_create_type_code());
	vnx::register_type_code(::pilot::base::UDP_SocketBase::static_create_type_code());
	vnx::register_type_code(::pilot::base::can_adapter_e::static_create_type_code());
	vnx::register_type_code(::pilot::base::can_error_class_e::static_create_type_code());
	vnx::register_type_code(::pilot::base::can_error_t::static_create_type_code());
	vnx::register_type_code(::pilot::base::in_address_t::static_create_type_code());
	vnx::register_type_code(::pilot::base::socketcan_options_t::static_create_type_code());
}

static struct vnx_static_init {
	vnx_static_init() {
		register_all_types();
	}
} vnx_static_init_;

const vnx::TypeCode* const vnx_native_type_code_CAN_Frame = vnx::get_type_code(vnx::Hash64(0x4d70a2725dc4def6ull));
const vnx::TypeCode* const vnx_native_type_code_CAN_ProxyBase = vnx::get_type_code(vnx::Hash64(0x17c6e6ba3900a740ull));
const vnx::TypeCode* const vnx_native_type_code_CAN_Proxy_send = vnx::get_type_code(vnx::Hash64(0xfac9f3d0e6b114e0ull));
const vnx::TypeCode* const vnx_native_type_code_CAN_Proxy_send_return = vnx::get_type_code(vnx::Hash64(0xd07ac71047b63fedull));
const vnx::TypeCode* const vnx_native_type_code_DataPacket = vnx::get_type_code(vnx::Hash64(0xcd0d2bd202ac0fb0ull));
const vnx::TypeCode* const vnx_native_type_code_NetworkStreamBase = vnx::get_type_code(vnx::Hash64(0xf148d90d9b345113ull));
const vnx::TypeCode* const vnx_native_type_code_NetworkStream_connect = vnx::get_type_code(vnx::Hash64(0x5d1ba9f28b73deffull));
const vnx::TypeCode* const vnx_native_type_code_NetworkStream_connect_return = vnx::get_type_code(vnx::Hash64(0x4e1ecb58b5748247ull));
const vnx::TypeCode* const vnx_native_type_code_NetworkStream_disconnect = vnx::get_type_code(vnx::Hash64(0x717989a7028c00b8ull));
const vnx::TypeCode* const vnx_native_type_code_NetworkStream_disconnect_return = vnx::get_type_code(vnx::Hash64(0x798dafe5dee15bd7ull));
const vnx::TypeCode* const vnx_native_type_code_NetworkStream_is_connected = vnx::get_type_code(vnx::Hash64(0x43ce78fb38d0a151ull));
const vnx::TypeCode* const vnx_native_type_code_NetworkStream_is_connected_return = vnx::get_type_code(vnx::Hash64(0xc9d1bce2bfaef9full));
const vnx::TypeCode* const vnx_native_type_code_SerialPortBase = vnx::get_type_code(vnx::Hash64(0x34145bbaf1d9d037ull));
const vnx::TypeCode* const vnx_native_type_code_SerialPort_close_port = vnx::get_type_code(vnx::Hash64(0x325a9542af22132full));
const vnx::TypeCode* const vnx_native_type_code_SerialPort_close_port_return = vnx::get_type_code(vnx::Hash64(0xeab3f48d8b486944ull));
const vnx::TypeCode* const vnx_native_type_code_SerialPort_open_port = vnx::get_type_code(vnx::Hash64(0xf8db604b35c6b25dull));
const vnx::TypeCode* const vnx_native_type_code_SerialPort_open_port_return = vnx::get_type_code(vnx::Hash64(0xbe277f383728e0full));
const vnx::TypeCode* const vnx_native_type_code_SocketSignal = vnx::get_type_code(vnx::Hash64(0x91f51fd310ed96deull));
const vnx::TypeCode* const vnx_native_type_code_UDP_SocketBase = vnx::get_type_code(vnx::Hash64(0xed63df42c27a66ebull));
const vnx::TypeCode* const vnx_native_type_code_can_adapter_e = vnx::get_type_code(vnx::Hash64(0x7a7d5bef82a9fdfcull));
const vnx::TypeCode* const vnx_native_type_code_can_error_class_e = vnx::get_type_code(vnx::Hash64(0x4529147bde76f57bull));
const vnx::TypeCode* const vnx_native_type_code_can_error_t = vnx::get_type_code(vnx::Hash64(0x2739d295fa73821cull));
const vnx::TypeCode* const vnx_native_type_code_in_address_t = vnx::get_type_code(vnx::Hash64(0xf0ba186b6082b1d2ull));
const vnx::TypeCode* const vnx_native_type_code_socketcan_options_t = vnx::get_type_code(vnx::Hash64(0x21d4bbca201847deull));

} // namespace pilot
} // namespace base


// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/JoystickClient.hxx>
#include <pilot/base/Joystick_close_device.hxx>
#include <pilot/base/Joystick_close_device_return.hxx>
#include <pilot/base/Joystick_open_device.hxx>
#include <pilot/base/Joystick_open_device_return.hxx>
#include <vnx/Module.h>
#include <vnx/ModuleInterface_vnx_get_type_code.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code_return.hxx>
#include <vnx/TopicPtr.hpp>

#include <vnx/vnx.h>


namespace pilot {
namespace base {

JoystickClient::JoystickClient(const std::string& service_name)
	:	Client::Client(vnx::Hash64(service_name))
{
}

JoystickClient::JoystickClient(vnx::Hash64 service_addr)
	:	Client::Client(service_addr)
{
}

::vnx::TypeCode JoystickClient::vnx_get_type_code() {
	auto _method = ::vnx::ModuleInterface_vnx_get_type_code::create();
	auto _return_value = vnx_request(_method);
	auto _result = std::dynamic_pointer_cast<const ::vnx::ModuleInterface_vnx_get_type_code_return>(_return_value);
	if(!_result) {
		throw std::logic_error("JoystickClient: !_result");
	}
	return _result->_ret_0;
}

void JoystickClient::open_device() {
	auto _method = ::pilot::base::Joystick_open_device::create();
	auto _return_value = vnx_request(_method);
}

void JoystickClient::open_device_async() {
	vnx_is_async = true;
	open_device();
}

void JoystickClient::close_device() {
	auto _method = ::pilot::base::Joystick_close_device::create();
	auto _return_value = vnx_request(_method);
}

void JoystickClient::close_device_async() {
	vnx_is_async = true;
	close_device();
}


} // namespace pilot
} // namespace base


// AUTO GENERATED by vnxcppcodegen

#include <pilot/base/package.hxx>
#include <pilot/base/JoystickMngClient.hxx>
#include <vnx/Module.h>
#include <vnx/ModuleInterface_vnx_get_type_code.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code_return.hxx>
#include <vnx/TopicPtr.hpp>

#include <vnx/vnx.h>


namespace pilot {
namespace base {

JoystickMngClient::JoystickMngClient(const std::string& service_name)
	:	Client::Client(vnx::Hash64(service_name))
{
}

JoystickMngClient::JoystickMngClient(vnx::Hash64 service_addr)
	:	Client::Client(service_addr)
{
}

::vnx::TypeCode JoystickMngClient::vnx_get_type_code() {
	auto _method = ::vnx::ModuleInterface_vnx_get_type_code::create();
	auto _return_value = vnx_request(_method);
	auto _result = std::dynamic_pointer_cast<const ::vnx::ModuleInterface_vnx_get_type_code_return>(_return_value);
	if(!_result) {
		throw std::logic_error("JoystickMngClient: !_result");
	}
	return _result->_ret_0;
}


} // namespace pilot
} // namespace base

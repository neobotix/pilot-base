
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_Joystick_ASYNC_CLIENT_HXX_
#define INCLUDE_pilot_base_Joystick_ASYNC_CLIENT_HXX_

#include <vnx/AsyncClient.h>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace pilot {
namespace base {

class JoystickAsyncClient : public vnx::AsyncClient {
public:
	JoystickAsyncClient(const std::string& service_name);
	
	JoystickAsyncClient(vnx::Hash64 service_addr);
	
	uint64_t close_device(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const std::exception&)>& _error_callback = std::function<void(const std::exception&)>());
	
	uint64_t open_device(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const std::exception&)>& _error_callback = std::function<void(const std::exception&)>());
	
	std::vector<uint64_t> vnx_get_pending_ids() const override;
	
protected:
	void vnx_purge_request(uint64_t _request_id, const std::exception& _ex) override;
	
	void vnx_callback_switch(uint64_t _request_id, std::shared_ptr<const vnx::Value> _value) override;
	
private:
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const std::exception&)>>> vnx_queue_close_device;
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const std::exception&)>>> vnx_queue_open_device;
	
};


} // namespace pilot
} // namespace base

#endif // INCLUDE_pilot_base_Joystick_ASYNC_CLIENT_HXX_

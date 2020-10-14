
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_UDP_Receiver_ASYNC_CLIENT_HXX_
#define INCLUDE_pilot_base_UDP_Receiver_ASYNC_CLIENT_HXX_

#include <vnx/AsyncClient.h>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace pilot {
namespace base {

class UDP_ReceiverAsyncClient : public vnx::AsyncClient {
public:
	UDP_ReceiverAsyncClient(const std::string& service_name);
	
	UDP_ReceiverAsyncClient(vnx::Hash64 service_addr);
	
	uint64_t vnx_get_config_object(
			const std::function<void(const ::vnx::Object&)>& _callback = std::function<void(const ::vnx::Object&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_get_config(const std::string& name, 
			const std::function<void(const ::vnx::Variant&)>& _callback = std::function<void(const ::vnx::Variant&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_set_config_object(const ::vnx::Object& config, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_set_config(const std::string& name, const ::vnx::Variant& value, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_get_type_code(
			const std::function<void(const ::vnx::TypeCode&)>& _callback = std::function<void(const ::vnx::TypeCode&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_restart(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_close(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t open_port(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t close_port(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	std::vector<uint64_t> vnx_get_pending_ids() const override;
	
protected:
	void vnx_purge_request(uint64_t _request_id, const vnx::exception& _ex) override;
	
	void vnx_callback_switch(uint64_t _request_id, std::shared_ptr<const vnx::Value> _value) override;
	
private:
	std::map<uint64_t, std::pair<std::function<void(const ::vnx::Object&)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_get_config_object;
	std::map<uint64_t, std::pair<std::function<void(const ::vnx::Variant&)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_get_config;
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_set_config_object;
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_set_config;
	std::map<uint64_t, std::pair<std::function<void(const ::vnx::TypeCode&)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_get_type_code;
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_restart;
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_close;
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_open_port;
	std::map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_close_port;
	
};


} // namespace pilot
} // namespace base

#endif // INCLUDE_pilot_base_UDP_Receiver_ASYNC_CLIENT_HXX_

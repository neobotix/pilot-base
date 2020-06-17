
// AUTO GENERATED by vnxcppcodegen

#include <vnx/vnx.h>
#include <pilot/base/package.hxx>
#include <pilot/base/UDP_ReceiverAsyncClient.hxx>
#include <pilot/base/UDP_Receiver_close_port.hxx>
#include <pilot/base/UDP_Receiver_close_port_return.hxx>
#include <pilot/base/UDP_Receiver_open_port.hxx>
#include <pilot/base/UDP_Receiver_open_port_return.hxx>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>



namespace pilot {
namespace base {

UDP_ReceiverAsyncClient::UDP_ReceiverAsyncClient(const std::string& service_name)
	:	AsyncClient::AsyncClient(vnx::Hash64(service_name))
{
}

UDP_ReceiverAsyncClient::UDP_ReceiverAsyncClient(vnx::Hash64 service_addr)
	:	AsyncClient::AsyncClient(service_addr)
{
}

uint64_t UDP_ReceiverAsyncClient::close_port(const std::function<void()>& _callback, const std::function<void(const std::exception&)>& _error_callback) {
	auto _method = ::pilot::base::UDP_Receiver_close_port::create();
	const auto _request_id = vnx_request(_method);
	vnx_queue_close_port[_request_id] = std::make_pair(_callback, _error_callback);
	vnx_num_pending++;
	return _request_id;
}

uint64_t UDP_ReceiverAsyncClient::open_port(const std::function<void()>& _callback, const std::function<void(const std::exception&)>& _error_callback) {
	auto _method = ::pilot::base::UDP_Receiver_open_port::create();
	const auto _request_id = vnx_request(_method);
	vnx_queue_open_port[_request_id] = std::make_pair(_callback, _error_callback);
	vnx_num_pending++;
	return _request_id;
}

std::vector<uint64_t> UDP_ReceiverAsyncClient::vnx_get_pending_ids() const {
	std::vector<uint64_t> _list;
	for(const auto& entry : vnx_queue_close_port) {
		_list.push_back(entry.first);
	}
	for(const auto& entry : vnx_queue_open_port) {
		_list.push_back(entry.first);
	}
	return _list;
}

void UDP_ReceiverAsyncClient::vnx_purge_request(uint64_t _request_id, const std::exception& _ex) {
	{
		const auto _iter = vnx_queue_close_port.find(_request_id);
		if(_iter != vnx_queue_close_port.end()) {
			if(_iter->second.second) {
				_iter->second.second(_ex);
			}
			vnx_queue_close_port.erase(_iter);
			vnx_num_pending--;
		}
	}
	{
		const auto _iter = vnx_queue_open_port.find(_request_id);
		if(_iter != vnx_queue_open_port.end()) {
			if(_iter->second.second) {
				_iter->second.second(_ex);
			}
			vnx_queue_open_port.erase(_iter);
			vnx_num_pending--;
		}
	}
}

void UDP_ReceiverAsyncClient::vnx_callback_switch(uint64_t _request_id, std::shared_ptr<const vnx::Value> _value) {
	const auto _type_hash = _value->get_type_hash();
	if(_type_hash == vnx::Hash64(0x5c1b70238fc1cba2ull)) {
		const auto _iter = vnx_queue_close_port.find(_request_id);
		if(_iter != vnx_queue_close_port.end()) {
			const auto _callback = std::move(_iter->second.first);
			vnx_queue_close_port.erase(_iter);
			vnx_num_pending--;
			if(_callback) {
				_callback();
			}
		} else {
			throw std::runtime_error("UDP_ReceiverAsyncClient: invalid return received");
		}
	}
	else if(_type_hash == vnx::Hash64(0xe3f9850d4fab4010ull)) {
		const auto _iter = vnx_queue_open_port.find(_request_id);
		if(_iter != vnx_queue_open_port.end()) {
			const auto _callback = std::move(_iter->second.first);
			vnx_queue_open_port.erase(_iter);
			vnx_num_pending--;
			if(_callback) {
				_callback();
			}
		} else {
			throw std::runtime_error("UDP_ReceiverAsyncClient: invalid return received");
		}
	}
	else {
		throw std::runtime_error("UDP_ReceiverAsyncClient: unknown return type");
	}
}


} // namespace pilot
} // namespace base

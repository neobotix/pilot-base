/*
 * CANopen_Proxy.h
 *
 *  Created on: Aug 19, 2025
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_CANOPEN_CANOPEN_PROXY_H_
#define INCLUDE_PILOT_BASE_CANOPEN_CANOPEN_PROXY_H_

#include <pilot/base/canopen/CANopen_ProxyBase.hxx>


namespace pilot {
namespace base {
namespace canopen {

class CANopen_Proxy : public CANopen_ProxyBase {
public:
	CANopen_Proxy(const std::string& _vnx_name);

protected:
	void init() override;
	void main() override;

	void upload_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const int32_t &timeout_ms, const vnx::request_id_t &_request_id) const override;
	void download_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const std::vector<uint8_t> &data, const int32_t &timeout_ms, const vnx::request_id_t &_request_id) override;
	void download_expedited_async(const uint32_t &node_id, const uint16_t &index, const uint8_t &subindex, const uint32_t &data, const uint32_t &num_bytes, const int32_t &timeout_ms, const vnx::request_id_t &_request_id) override;
	void map_pdo_async(const uint32_t &node_id, const uint32_t &pdo_type, const std::vector<object_entry_t> &objects, const bool &rtr, const int32_t &timeout_ms, const vnx::request_id_t &_request_id) override;
	void pdo_sync_async(const uint32_t &node_id, const uint32_t &pdo_type, const uint8_t &sync_divider, const int32_t &timeout_ms, const vnx::request_id_t &_request_id) override;

	void handle(std::shared_ptr<const CAN_Frame> sample) override;
	void handle(std::shared_ptr<const PDO> sample) override;

private:
	struct sdo_request_t{
		std::function<void(const std::string &)> callback_error_what;
		uint32_t node_id;
		uint16_t index;
		uint8_t subindex;
		int64_t timeout = 0;
		std::shared_ptr<const CAN_Frame> initial_frame;
		struct{
			std::function<void(const std::vector<uint8_t> &)> callback;
			std::pair<std::shared_ptr<const CAN_Frame>, std::shared_ptr<const CAN_Frame>> frames;
			bool toggle = true;
			std::vector<uint8_t> data;
		} upload;
		struct{
			std::function<void()> callback;
			std::vector<std::shared_ptr<const CAN_Frame>> segmented_frames;
			size_t index = 0;
		} download;
		std::shared_ptr<sdo_request_t> next;
	};
	mutable std::map<std::tuple<uint32_t, uint16_t, uint8_t>, sdo_request_t> sdo_requests;
	std::map<uint32_t, nmt_state_e> node_states;
	bool is_network_init = false;
	std::shared_ptr<vnx::Timer> init_timer;

	const node_t &find_node(uint32_t node_id) const;
	std::shared_ptr<sdo_request_t> upload_internal(uint32_t node_id, uint16_t index, uint8_t subindex, int32_t timeout_ms) const;
	std::shared_ptr<sdo_request_t> download_internal(uint32_t node_id, uint16_t index, uint8_t subindex, const std::vector<uint8_t> &data, int32_t timeout_ms) const;
	std::shared_ptr<sdo_request_t> download_expedited_internal(uint32_t node_id, uint16_t index, uint8_t subindex, uint32_t data, uint32_t num_bytes, int32_t timeout_ms) const;
	void check_request_timeouts();
	void network_reset();
	void sync() const;
	void heartbeat() const;
};


} // canopen
} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CANOPEN_CANOPEN_PROXY_H_ */


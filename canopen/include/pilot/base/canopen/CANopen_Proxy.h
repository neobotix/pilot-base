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

	void handle(std::shared_ptr<const CAN_Frame> sample) override;
	void handle(std::shared_ptr<const PDO> sample) override;

private:
	struct sdo_request_t{
		vnx::request_id_t request_id;
		uint32_t node_id;
		uint16_t index;
		uint8_t subindex;
		int64_t timeout = 0;
		struct{
			std::pair<std::shared_ptr<const CAN_Frame>, std::shared_ptr<const CAN_Frame>> frames;
			bool toggle = true;
			std::vector<uint8_t> data;
		} upload;
		struct{
			std::vector<std::shared_ptr<const CAN_Frame>> segmented_frames;
			size_t index = 0;
			bool expedited_request = false;
		} download;
	};
	mutable std::map<std::tuple<uint32_t, uint16_t, uint8_t>, sdo_request_t> sdo_requests;
	std::map<uint32_t, nmt_state_e> node_states;
	bool is_network_init = false;
	std::shared_ptr<vnx::Timer> init_timer;

	const node_t &find_node(uint32_t node_id) const;
	void check_request_timeouts();
	void network_reset();
	void sync() const;
	void heartbeat() const;
};


} // canopen
} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CANOPEN_CANOPEN_PROXY_H_ */


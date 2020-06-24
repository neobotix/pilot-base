/*
 * UDP_Receiver.h
 *
 *  Created on: Jun 3, 2020
 *      Author: mad
 */

#ifndef INCLUDE_PILOT_BASE_UDP_RECEIVER_H_
#define INCLUDE_PILOT_BASE_UDP_RECEIVER_H_

#include <pilot/base/UDP_ReceiverBase.hxx>

#include <atomic>


namespace pilot {
namespace base {

class UDP_Receiver : public UDP_ReceiverBase {
public:
	UDP_Receiver(const std::string& _vnx_name);

protected:
	void main() override;

	void open_port() override;

	void close_port() override;

private:
	ssize_t recv_packet(void* buf, size_t len, int timeout_ms) const;

	void read_loop(const vnx::Hash64 module_addr) const noexcept;

	void print_stats();

private:
	std::atomic<int> m_fd {-1};

	mutable volatile size_t m_bytes_recv = 0;
	mutable volatile size_t m_packet_counter = 0;

};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_UDP_RECEIVER_H_ */

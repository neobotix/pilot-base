/*
 * UDP_Socket.h
 *
 *  Created on: Apr 23, 2024
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_UDP_SOCKET_H_
#define INCLUDE_PILOT_BASE_UDP_SOCKET_H_

#include <pilot/base/UDP_SocketBase.hxx>


namespace pilot {
namespace base {

class UDP_Socket : public UDP_SocketBase {
public:
	UDP_Socket(const std::string& _vnx_name);

protected:
	void main() override;
	void handle(std::shared_ptr<const DataPacket> value) override;

private:
	using socket_t = int;
#ifndef _WIN32
	const socket_t INVALID_SOCKET = -1;
#endif
	socket_t socket;
	bool is_initialized = false;
	std::thread read_thread;

	std::atomic<size_t> packets_received;
	std::atomic<size_t> bytes_received;
	std::atomic<size_t> msg_sent;
	std::atomic<size_t> packets_sent;
	std::atomic<size_t> bytes_sent;

	void initialize();
	void cleanup();
	ssize_t receive(socket_t socket, void *data, size_t length, int timeout_ms) const;
	void print_stats();
	void read_loop();
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_UDP_SOCKET_H_ */


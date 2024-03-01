/*
 * udp.cpp
 *
 *  Created on: Mar 1, 2024
 *      Author: jaw
 */

#include <pilot/base/udp.h>

#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>


namespace pilot {
namespace base {

ssize_t udp_recv_packet(int socket, void* buf, size_t len, int timeout_ms)
{
	if(socket < 0) {
		throw std::logic_error("port not open");
	}

	if(timeout_ms >= 0)
	{
		::fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(socket, &read_set);

		struct timeval timeout = {int32_t(timeout_ms / 1000), int32_t((timeout_ms % 1000) * 1000)};
		if(::select(socket + 1, &read_set, 0, 0, &timeout) < 1) {
			return 0;
		}
	}
	const auto num_bytes = ::recvfrom(socket, buf, len, 0, 0, 0);
	if(num_bytes < 0) {
		throw std::runtime_error("recvfrom() failed with: " + std::string(strerror(errno)));
	}
	return num_bytes;
}


} // base
} // pilot

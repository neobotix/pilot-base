/*
 * UDP_Receiver.cpp
 *
 *  Created on: Jun 3, 2020
 *      Author: mad
 */

#include <pilot/base/UDP_Receiver.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>


namespace pilot {
namespace base {

void UDP_Receiver::open_port()
{
	close_port();

	m_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
	if(m_fd < 0) {
		throw std::runtime_error("socket() failed with: " + std::string(std::strerror(errno)));
	}

	::sockaddr_in myaddr;
	memset((char*)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port);
	if(::bind(m_fd, (::sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
		throw std::runtime_error("bind() failed with: " + std::string(std::strerror(errno)));
	}
}

void UDP_Receiver::close_port()
{
	if(m_fd >= 0) {
		::close(m_fd);
		m_fd = -1;
	}
}

ssize_t UDP_Receiver::recv_packet(void* buf, size_t len, int timeout_ms) const
{
	if(m_fd < 0) {
		throw std::logic_error("port not open");
	}

	if(timeout_ms >= 0)
	{
		::fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(m_fd, &read_set);

		struct timeval timeout = {int32_t(timeout_ms / 1000), int32_t((timeout_ms % 1000) * 1000)};
		if(::select(m_fd + 1, &read_set, 0, 0, &timeout) < 1) {
			return 0;
		}
	}
	const auto num_bytes = ::recvfrom(m_fd, buf, len, 0, 0, 0);
	if(num_bytes < 0) {
		throw std::runtime_error("recvfrom() error: " + std::string(std::strerror(errno)));
	}
	return num_bytes;
}


} // base
} // pilot

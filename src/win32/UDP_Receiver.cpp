/*
 * UDP_Receiver.cpp
 *
 *  Created on: Jun 3, 2020
 *      Author: jaw
 */

#include <pilot/base/UDP_Receiver.h>

#include <winsock2.h>


namespace pilot {
namespace base {

void UDP_Receiver::open_port()
{
	close_port();
	m_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_fd < 0) {
		throw std::runtime_error("socket() failed with: " + std::to_string(WSAGetLastError()));
	}

	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if(::bind(m_fd, (sockaddr *)&addr, sizeof(addr)) == -1){
		throw std::runtime_error("bind() failed with: " + std::to_string(WSAGetLastError()));
	}
}

void UDP_Receiver::close_port()
{
	if(m_fd == -1) return;

	closesocket(m_fd);
	m_fd = -1;
}

ssize_t UDP_Receiver::recv_packet(void* buf, size_t len, int timeout_ms) const
{
	if(timeout_ms >= 0){
		fd_set fdset;
		FD_ZERO(&fdset);
		FD_SET(m_fd, &fdset);
		timeval tv = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};

		int ret = select(m_fd+1, &fdset, NULL, NULL, &tv);
		if(ret < 1) return 0;
	}

	ssize_t result = recv(m_fd, (char*)buf, len, 0);
	if(result == -1){
		throw std::runtime_error("recv() error: " + std::to_string(WSAGetLastError()));
	}

	return result;
}


} // base
} // pilot

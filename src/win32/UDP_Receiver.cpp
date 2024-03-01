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


} // base
} // pilot

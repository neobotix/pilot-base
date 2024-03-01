/*
 * udp.cpp
 *
 *  Created on: Mar 1, 2024
 *      Author: jaw
 */

#include <pilot/base/udp.h>

#include <winsock2.h>


namespace pilot {
namespace base {


ssize_t udp_recv_packet(int socket, void* buf, size_t len, int timeout_ms)
{
	if(timeout_ms >= 0){
		fd_set fdset;
		FD_ZERO(&fdset);
		FD_SET(socket, &fdset);
		timeval tv = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};

		int ret = select(socket+1, &fdset, NULL, NULL, &tv);
		if(ret < 1) return 0;
	}

	ssize_t result = recv(socket, (char*)buf, len, 0);
	if(result == -1){
		throw std::runtime_error("recv() failed with: " + std::to_string(WSAGetLastError()));
	}

	return result;
}


} // base
} // pilot

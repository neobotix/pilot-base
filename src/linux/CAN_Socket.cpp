/*
 * CAN_Socket.cpp
 *
 *  Created on: Jun 10, 2020
 *      Author: mad
 */

#include <pilot/base/CAN_Socket.h>

#include <vnx/vnx.h>

#include <string>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


namespace pilot {
namespace base {

CAN_Socket::CAN_Socket(const std::string& iface)
{
	sock = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if(sock < 0) {
		throw std::runtime_error("socket() failed with: " + std::string(strerror(errno)));
	}

	ifreq ifr = {};
	::strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ - 1);
	if(::ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
		throw std::runtime_error("ioctl() failed with: " + std::string(strerror(errno)));
	}

	sockaddr_can addr = {};
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if(::bind(sock, (sockaddr*)(&addr), sizeof(addr)) < 0) {
		throw std::runtime_error("bind() failed with: " + std::string(strerror(errno)));
	}
}

CAN_Socket::~CAN_Socket() {
	close();
}

void CAN_Socket::close()
{
	if(sock >= 0) {
		::close(sock);
		sock = -1;
	}
}

bool CAN_Socket::read(CAN_Frame &frame, int timeout_ms)
{
	if(timeout_ms >= 0){
		::fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(sock, &read_set);

		struct timeval timeout = {int32_t(timeout_ms / 1000), int32_t((timeout_ms % 1000) * 1000)};
		if(::select(sock + 1, &read_set, 0, 0, &timeout) < 1) {
			return false;
		}
	}

	::can_frame data = {};
	const auto res = ::read(sock, &data, sizeof(data));
	if(res != sizeof(data)) {
		throw std::runtime_error("read() failed with: " + std::string(strerror(errno)));
	}

	frame.time = vnx::get_time_micros();
	frame.id = data.can_id & 0x1FFFFFFF;
	frame.size = data.can_dlc;
	for(int i = 0; i < 8; ++i) {
		frame.data[i] = data.data[i];
	}
	return true;
}

void CAN_Socket::write(const CAN_Frame& frame)
{
	::can_frame out = {};
	out.can_id = frame.id;
	out.can_dlc = frame.size;
	for(int i = 0; i < 8; ++i) {
		out.data[i] = frame.data[i];
	}

	const auto res = ::write(sock, &out, sizeof(out));
	if(res != sizeof(out)) {
		throw std::runtime_error("write() failed with: " + std::string(strerror(errno)));
	}
}


} // base
} // pilot

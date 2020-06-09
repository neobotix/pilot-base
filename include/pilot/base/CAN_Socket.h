/*
 * Socket.h
 *
 *  Created on: Nov 23, 2017
 *      Author: mad
 */

#ifndef INCLUDE_CANSOCKET_H_
#define INCLUDE_CANSOCKET_H_

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

#include <automy/can/Frame.hxx>
#include <vnx/Time.h>


namespace automy {
namespace can {

class Socket {
public:
	Socket(std::string iface) {
		sock = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
		if(sock < 0) {
			throw std::runtime_error("socket() failed!");
		}
		ifreq ifr = {};
		::strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ);
		if(::ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
			throw std::runtime_error("ioctl() failed!");
		}
		sockaddr_can addr = {};
		addr.can_family = AF_CAN;
		addr.can_ifindex = ifr.ifr_ifindex;
		if(::bind(sock, (sockaddr*)(&addr), sizeof(addr)) < 0) {
			throw std::runtime_error("bind() failed!");
		}
	}
	
	~Socket() {
		shutdown();
		close();
	}
	
	void shutdown() {
		if(sock >= 0) {
			::shutdown(sock, SHUT_RDWR);
		}
	}
	
	void close() {
		if(sock >= 0) {
			::close(sock);
			sock = -1;
		}
	}
	
	Frame read() {
		can_frame frame = {};
		int res = ::read(sock, &frame, sizeof(frame));
		if(res != sizeof(frame)) {
			throw std::runtime_error("read() failed with: " + std::string(strerror(errno)));
		}
		Frame out;
		out.time = vnx::get_time_micros();
		out.id = frame.can_id & 0x1FFFFFFF;
		out.size = frame.can_dlc;
		for(int i = 0; i < 8; ++i) {
			out.data[i] = frame.data[i];
		}
		return out;
	}
	
	void write(const Frame& frame) {
		can_frame out = {};
		out.can_id = frame.id;
		out.can_dlc = frame.size;
		for(int i = 0; i < 8; ++i) {
			out.data[i] = frame.data[i];
		}
		int res = ::write(sock, &out, sizeof(out));
		if(res != sizeof(out)) {
			throw std::runtime_error("write() failed with: " + std::string(strerror(errno)));
		}
	}
	
private:
	int sock = -1;
	
};


} // can
} // automy

#endif /* INCLUDE_CANSOCKET_H_ */

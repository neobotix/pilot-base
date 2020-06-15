/*
 * CAN_Socket.cpp
 *
 *  Created on: Jun 15, 2020
 *      Author: jaw
 */

#include <pilot/base/CAN_Socket.h>

#include <vnx/vnx.h>



namespace pilot {
namespace base {

// No SocketCAN on Windows

CAN_Socket::CAN_Socket(const std::string& iface)
{
}

CAN_Socket::~CAN_Socket() {
}

void CAN_Socket::close()
{
}

CAN_Frame CAN_Socket::read()
{
	CAN_Frame out;
	out.time = vnx::get_time_micros();
	out.id = 0;
	out.size = 0;
	for(int i = 0; i < 8; ++i) {
		out.data[i] = 0;
	}
	return out;
}

void CAN_Socket::write(const CAN_Frame& frame)
{
}


} // base
} // pilot

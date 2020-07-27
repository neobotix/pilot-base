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

bool CAN_Socket::read(CAN_Frame &frame, int timeout_ms)
{
	return false;
}

void CAN_Socket::write(const CAN_Frame& frame)
{
}


} // base
} // pilot

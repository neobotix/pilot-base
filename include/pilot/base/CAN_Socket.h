/*
 * Socket.h
 *
 *  Created on: Nov 23, 2017
 *      Author: mad
 */

#ifndef INCLUDE_PILOT_BASE_CAN_SOCKET_H_
#define INCLUDE_PILOT_BASE_CAN_SOCKET_H_

#include <pilot/base/CAN_Frame.hxx>


namespace pilot {
namespace base {

class CAN_Socket {
public:
	CAN_Socket(const std::string& iface);
	
	~CAN_Socket();
	
	void close();
	
	CAN_Frame read();
	
	void write(const CAN_Frame& frame);
	
private:
	int sock = -1;
	
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_SOCKET_H_ */

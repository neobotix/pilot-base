/*
 * Socket.h
 *
 *  Created on: Nov 23, 2017
 *      Author: mad
 */

#ifndef INCLUDE_PILOT_BASE_CAN_SOCKET_H_
#define INCLUDE_PILOT_BASE_CAN_SOCKET_H_

#include <pilot/base/CAN_Frame.hxx>
#include <pilot/base/CAN_Interface.h>


namespace pilot {
namespace base {

class CAN_Socket : public CAN_Interface {
public:
	CAN_Socket(const std::string& iface, const socketcan_options_t &socket_options);
	
	~CAN_Socket();
	
	void close() override;
	
	bool read(CAN_Frame &frame, int timout_ms) override;
	
	void write(const CAN_Frame& frame) override;
	
private:
	int sock = -1;
	
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_SOCKET_H_ */

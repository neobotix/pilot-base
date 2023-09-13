/*
 * UDP_Sender.h
 *
 *  Created on: Sep 12, 2023
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_UDP_SENDER_H_
#define INCLUDE_PILOT_BASE_UDP_SENDER_H_

#include <pilot/base/UDP_SenderBase.hxx>


namespace pilot {
namespace base {

class UDP_Sender : public UDP_SenderBase {
public:
	UDP_Sender(const std::string& _vnx_name);

protected:
	void main() override;

	void handle(std::shared_ptr<const DataPacket> value) override;

private:
	using socket_t = int;
#ifndef _WIN32
	const socket_t INVALID_SOCKET = -1;
#endif
	socket_t socket;
	size_t packet_counter = 0;
	size_t bytes_sent = 0;

	void setup();
	void cleanup();
	void print_stats();

};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_UDP_SENDER_H_ */

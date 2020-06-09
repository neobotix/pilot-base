/*
 * Proxy.h
 *
 *  Created on: Jan 22, 2018
 *      Author: mad
 */

#ifndef CAN_INCLUDE_CAN_PROXY_H_
#define CAN_INCLUDE_CAN_PROXY_H_

#include <automy/can/ProxyBase.hxx>
#include <automy/can/Socket.h>


namespace automy {
namespace can {

class Proxy : public ProxyBase {
public:
	Proxy(const std::string& _vnx_name);
	
protected:
	void main() override;
	
	void handle(std::shared_ptr<const can::Frame> value) override;
	
	void print_stats();
	
	void read_loop(std::shared_ptr<vnx::Topic> topic);
	
private:
	std::shared_ptr<can::Socket> socket;
	
	int64_t num_read = 0;
	int64_t num_write = 0;
	
};


} // can
} // automy

#endif /* CAN_INCLUDE_CAN_PROXY_H_ */

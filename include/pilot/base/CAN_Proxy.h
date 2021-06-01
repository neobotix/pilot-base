/*
 * Proxy.h
 *
 *  Created on: Jan 22, 2018
 *      Author: mad
 */

#ifndef INCLUDE_PILOT_BASE_CAN_PROXY_H_
#define INCLUDE_PILOT_BASE_CAN_PROXY_H_

#include <pilot/base/CAN_ProxyBase.hxx>
#include <pilot/base/CAN_Interface.h>


namespace pilot {
namespace base {

class CAN_Proxy : public CAN_ProxyBase {
public:
	CAN_Proxy(const std::string& _vnx_name);
	
protected:
	void init() override;

	void main() override;
	
	void send(const CAN_Frame& frame) override;

	void handle(std::shared_ptr<const CAN_Frame> value) override;
	
	bool vnx_shutdown() override;

	void print_stats();
	
	void read_loop();
	
private:
	std::shared_ptr<CAN_Interface> socket;
	
	int64_t num_read = 0;
	int64_t num_write = 0;
	int64_t num_write_fail = 0;
	
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_PROXY_H_ */

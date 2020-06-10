/*
 * Proxy.cpp
 *
 *  Created on: Jan 22, 2018
 *      Author: mad
 */

#include <pilot/base/CAN_Proxy.h>


namespace pilot {
namespace base {

CAN_Proxy::CAN_Proxy(const std::string& _vnx_name)
	:	CAN_ProxyBase(_vnx_name)
{
}

void CAN_Proxy::main()
{
	subscribe(input, 10);
	
	set_timer_millis(stats_interval_ms, std::bind(&CAN_Proxy::print_stats, this));

	socket = std::make_shared<CAN_Socket>(device);

	std::thread thread(&CAN_Proxy::read_loop, this);
	
	Super::main();
	
	socket->close();			// close socket to make read_loop() exit
	thread.join();				// wait for read_loop()
}

void CAN_Proxy::handle(std::shared_ptr<const CAN_Frame> value)
{
	try {
		socket->write(*value);
		num_write++;
	}
	catch(const std::exception& ex) {
		log(WARN).out << ex.what();
	}
}

void CAN_Proxy::print_stats()
{
	log(INFO).out << (1000 * num_read) / stats_interval_ms << " msgs/s receive, "
				<< (1000 * num_write) / stats_interval_ms << " msgs/s send";
	num_read = 0;
	num_write = 0;
}

void CAN_Proxy::read_loop()
{
	while(vnx_do_run())
	{
		try {
			CAN_Frame frame = socket->read();
			frame.is_big_endian = is_big_endian;
			publish(frame, output);
			num_read++;
		}
		catch(const std::exception& ex) {
			if(vnx_do_run()) {
				log(WARN).out << "read() failed with: " << ex.what();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
	}
}


} // base
} // pilot

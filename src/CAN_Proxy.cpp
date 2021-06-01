/*
 * Proxy.cpp
 *
 *  Created on: Jan 22, 2018
 *      Author: mad
 */

#include <pilot/base/CAN_Proxy.h>
#ifdef _WIN32
#include <pilot/base/CAN_PeakUSB.h>
#else
#include <pilot/base/CAN_Socket.h>
#endif


namespace pilot {
namespace base {

CAN_Proxy::CAN_Proxy(const std::string& _vnx_name)
	:	CAN_ProxyBase(_vnx_name)
{
}

void CAN_Proxy::init()
{
	subscribe(input, 10);
}

void CAN_Proxy::main()
{
	set_timer_millis(stats_interval_ms, std::bind(&CAN_Proxy::print_stats, this));

	switch(adapter){
#ifdef _WIN32
	case can_adapter_e::PEAKUSB:
		socket = std::make_shared<CAN_PeakUSB>(baud_rate);
		break;
#else
	case can_adapter_e::SOCKETCAN:
		socket = std::make_shared<CAN_Socket>(device);
		break;
#endif
	default:
		throw std::runtime_error("CAN adapter not available on this platform");
	}

	std::thread thread(&CAN_Proxy::read_loop, this);
	
	Super::main();
	
	socket->close();			// close socket to make read_loop() exit
	thread.join();				// wait for read_loop()
}

void CAN_Proxy::send(const CAN_Frame& frame)
{
	num_write_fail++;
	socket->write(frame);
	num_write_fail--;
	num_write++;
}

void CAN_Proxy::handle(std::shared_ptr<const CAN_Frame> value)
{
	try {
		send(*value);
	}
	catch(const std::exception& ex) {
		log(WARN).out << ex.what();
	}
}

bool CAN_Proxy::vnx_shutdown()
{
	if(shutdown_delay_ms <= 0) {
		return true;
	}
	set_timeout_millis(shutdown_delay_ms, std::bind(&CAN_Proxy::exit, this));
	return false;
}

void CAN_Proxy::print_stats()
{
	log(INFO).out << (1000 * num_read) / stats_interval_ms << " msgs/s receive, "
				<< (1000 * num_write) / stats_interval_ms << " msgs/s send, "
				<< num_write_fail << " failed";
	num_read = 0;
	num_write = 0;
}

void CAN_Proxy::read_loop()
{
	while(vnx_do_run())
	{
		try {
			CAN_Frame frame;
			if(socket->read(frame, read_timeout_ms)){
				frame.is_big_endian = is_big_endian;
				publish(frame, output);
				num_read++;
			}
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

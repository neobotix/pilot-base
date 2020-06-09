/*
 * Proxy.cpp
 *
 *  Created on: Jan 22, 2018
 *      Author: mad
 */

#include <automy/can/Proxy.h>


namespace automy {
namespace can {

Proxy::Proxy(const std::string& _vnx_name) : ProxyBase(_vnx_name) {}

void Proxy::main() {
	subscribe(input);
	set_timer_millis(1000, std::bind(&Proxy::print_stats, this));
	
	socket = std::make_shared<can::Socket>(device);
	std::thread thread(&Proxy::read_loop, this, output);
	
	Super::main();
	
	socket->shutdown();
	socket->close();			// somehow shutdown does not work, so we close it here already
	thread.join();
}

void Proxy::handle(std::shared_ptr<const can::Frame> value) {
	try {
		socket->write(*value);
		num_write++;
	} catch(std::exception& ex) {
		log(WARN).out << ex.what();
	}
}

void Proxy::print_stats() {
	log(INFO).out << num_read << " msgs/s receiving, " << num_write << " msgs/s sending";
	num_read = 0;
	num_write = 0;
}

void Proxy::read_loop(std::shared_ptr<vnx::Topic> topic) {
	vnx::Publisher publisher;
	while(true) {
		try {
			can::Frame frame = socket->read();
			frame.is_big_endian = is_big_endian;
			publisher.publish(frame, topic);
			num_read++;
		} catch(...) {
			break;
		}
	}
}


} // can
} // automy

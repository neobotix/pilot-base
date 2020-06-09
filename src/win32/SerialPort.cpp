/*
 * SerialPort.cpp
 *
 *  Created on: May 27, 2020
 *      Author: mad
 */

#include <pilot/sensors/SerialPort.h>


namespace pilot {
namespace sensors {

void SerialPort::open_port()
{
	close_port();

	// TODO

	log(INFO).out << "Opened port '" << port << "'";
}

void SerialPort::close_port()
{
	if(m_fd >= 0) {
		// TODO
		m_fd = -1;
	}
}

ssize_t SerialPort::read_port(void* buf, size_t len, int timeout_ms) const
{
	// TODO
	return 0;
}

ssize_t SerialPort::write_port(const void* buf, size_t len) const
{
	// TODO
	return 0;
}


} // sensors
} // pilot

/*
 * SerialPort.cpp
 *
 *  Created on: May 27, 2020
 *      Author: mad
 */

#include <pilot/base/SerialPort.h>


namespace pilot {
namespace base {

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
		m_fd = INVALID_HANDLE_VALUE;
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


} // base
} // pilot

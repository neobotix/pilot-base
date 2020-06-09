/*
 * SerialPort.cpp
 *
 *  Created on: May 27, 2020
 *      Author: mad
 */

#include <pilot/sensors/SerialPort.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/select.h>
#include <linux/serial.h>
#include <arpa/inet.h>


namespace pilot {
namespace sensors {

void SerialPort::open_port()
{
	close_port();

	// open serial port
	m_fd = ::open(port.c_str(), O_RDWR | O_NOCTTY);

	if(m_fd < 0) {
		throw std::runtime_error("open('" + port + "') failed with: " + std::string(std::strerror(errno)));
	}

	int baud_code = -1;
	switch(baud_rate)
	{
		case 115200: baud_code = B115200; break;
		case 230400: baud_code = B230400; break;
		case 500000: baud_code = B500000; break;
		case 1000000: baud_code = B1000000; break;
	}

	// configure serial port
	termios options = {};
	tcgetattr(m_fd, &options);				// get current config

	if(raw_mode) {
		cfmakeraw(&options);				// configure for binary data
	}

	options.c_cflag &= ~CSTOPB;				// one stop bit
	options.c_cflag &= ~CRTSCTS;			// no hardware handshake
	options.c_cflag |= CLOCAL | CREAD;		// legacy magic

	options.c_cc[VMIN] = 1;					// read at least one byte per read() call
	options.c_cc[VTIME] = 0;				// inter-byte timeout (not needed here)

	if(baud_code >= 0) {
		cfsetispeed(&options, baud_code);	// input baudrate
		cfsetospeed(&options, baud_code);	// output baudrate
	} else {
		cfsetispeed(&options, B38400);		// this is needed for some reason
		cfsetospeed(&options, B38400);		// this is needed for some reason
	}

	tcsetattr(m_fd, TCSANOW, &options);		// apply the new config

	if(baud_code < 0) {
		// set custom baud rate
		struct serial_struct ss;
		ioctl(m_fd, TIOCGSERIAL, &ss);
		ss.flags |= ASYNC_SPD_CUST;
		ss.custom_divisor = ss.baud_base / baud_rate;
		ioctl(m_fd, TIOCSSERIAL, &ss);
	}

	log(INFO) << "Opened port '" << port << "'";
}

void SerialPort::close_port()
{
	if(m_fd >= 0) {
		::close(m_fd);
		m_fd = -1;
	}
}

ssize_t SerialPort::read_port(void* buf, size_t len, int timeout_ms) const
{
	if(m_fd < 0) {
		throw std::logic_error("port not open");
	}

	if(timeout_ms >= 0)
	{
		::fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(m_fd, &read_set);

		struct timeval timeout = {int32_t(timeout_ms / 1000), int32_t((timeout_ms % 1000) * 1000)};
		if(::select(m_fd + 1, &read_set, 0, 0, &timeout) < 1) {
			return 0;
		}
	}
	const auto num_bytes = ::read(m_fd, buf, len);
	if(num_bytes < 0) {
		throw std::runtime_error("read() error: " + std::string(std::strerror(errno)));
	}
	return num_bytes;
}

ssize_t SerialPort::write_port(const void* buf, size_t len) const
{
	return ::write(m_fd, buf, len);
}


} // sensors
} // pilot

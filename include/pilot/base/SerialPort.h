/*
 * SerialPort.h
 *
 *  Created on: May 27, 2020
 *      Author: mad
 */

#ifndef INCLUDE_NEO_SENSORS_SERIALPORT_H_
#define INCLUDE_NEO_SENSORS_SERIALPORT_H_

#include <pilot/sensors/SerialPortBase.hxx>

#include <atomic>


namespace pilot {
namespace sensors {

class SerialPort : public SerialPortBase {
public:
	SerialPort(const std::string& _vnx_name);

protected:
	void main() override;

	void open_port() override;

	void close_port() override;

	void handle(std::shared_ptr<const automy::basic::DataPacket> value) override;

private:
	void signal();

	void print_stats();

	ssize_t read_port(void* buf, size_t len, int timeout_ms) const;

	ssize_t write_port(const void* buf, size_t len) const;

	void read_loop(const vnx::Hash64 module_addr) const;

private:
#ifdef _WIN32
	// TODO
#else
	std::atomic<int> m_fd {-1};
#endif

	mutable volatile size_t m_bytes_read = 0;
	mutable volatile size_t m_bytes_write = 0;

};


} // sensors
} // pilot


#endif /* INCLUDE_NEO_SENSORS_SERIALPORT_H_ */

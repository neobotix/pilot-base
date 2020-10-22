/*
 * SerialPort.h
 *
 *  Created on: May 27, 2020
 *      Author: mad
 */

#ifndef INCLUDE_PILOT_BASE_SERIALPORT_H_
#define INCLUDE_PILOT_BASE_SERIALPORT_H_

#include <pilot/base/SerialPortBase.hxx>

#include <atomic>


namespace pilot {
namespace base {

class SerialPort : public SerialPortBase {
public:
	SerialPort(const std::string& _vnx_name);

protected:
	void init() override;

	void main() override;

	void open_port() override;

	void close_port() override;

	void handle(std::shared_ptr<const DataPacket> value) override;

	bool vnx_shutdown() override;

private:
	void signal();

	void print_stats();

	ssize_t read_port(void* buf, size_t len, int timeout_ms) const;

	ssize_t write_port(const void* buf, size_t len) const;

	void read_loop(const vnx::Hash64 module_addr) const;

private:
#ifdef _WIN32
	void* m_fd = (void*)-1;
#else
	std::atomic<int> m_fd {-1};
#endif

	mutable volatile size_t m_bytes_read = 0;
	mutable volatile size_t m_bytes_write = 0;

};


} // base
} // pilot


#endif /* INCLUDE_PILOT_BASE_SERIALPORT_H_ */

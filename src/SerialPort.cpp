/*
 * SerialPort.cpp
 *
 *  Created on: May 27, 2020
 *      Author: mad
 */

#include <pilot/base/SerialPort.h>
#include <pilot/base/SerialPortClient.hxx>
#include <pilot/base/SocketSignal.hxx>


namespace pilot {
namespace base {

SerialPort::SerialPort(const std::string& _vnx_name)
	:	SerialPortBase(_vnx_name)
{
}

void SerialPort::init()
{
	subscribe(input, 100);					// receive binary data packets
}

void SerialPort::main()
{
	if(signal_interval_ms) {
		set_timer_millis(signal_interval_ms, std::bind(&SerialPort::signal, this));
	}
	if(stats_interval_ms) {
		set_timer_millis(stats_interval_ms, std::bind(&SerialPort::print_stats, this));
	}

	// make sure port is opened before entering Super::main()
	try {
		open_port();
	}
	catch(const vnx::exception& ex) {
		log(WARN) << ex.value()->what;
	}

	// start read loop
	std::thread read_thread;
	{
		// open a private pipe for read_loop()
		const auto module_addr = vnx::Hash64::rand();
		vnx::open_pipe(module_addr, this, UNLIMITED);
		// start read thread
		read_thread = std::thread(&SerialPort::read_loop, this, module_addr);
	}

	Super::main();

	if(read_thread.joinable()) {
		read_thread.join();
	}
	close_port();
}

void SerialPort::handle(std::shared_ptr<const DataPacket> value)
{
	if(m_fd < 0) {
		return;
	}
	const auto num_written = write_port(value->payload.data(), value->payload.size());
	if(num_written == -1 || (size_t)num_written != value->payload.size()) {
		log(WARN) << "Failed to write " << value->payload.size() << " bytes!";
	}
	if(num_written > 0) {
		m_bytes_write += num_written;
	}
}

bool SerialPort::vnx_shutdown()
{
	if(shutdown_delay_ms <= 0) {
		return true;
	}
	set_timeout_millis(shutdown_delay_ms, std::bind(&SerialPort::exit, this));
	return false;
}

void SerialPort::read_loop(const vnx::Hash64 module_addr) const
{
	SerialPortClient client(module_addr);

	while(vnx_do_run())
	{
		while(vnx_do_run())
		{
			try {
				auto sample = DataPacket::create();
				sample->time = vnx::get_time_micros();
				sample->payload.resize(4096);

				// read data
				const auto num_bytes = read_port(sample->payload.data(), sample->payload.size(), read_timeout_ms);
				if(num_bytes > 0) {
					sample->payload.resize(num_bytes);
					publish(sample, output, BLOCKING);
					m_bytes_read += num_bytes;
				}
			}
			catch(const std::exception& ex) {
				if(vnx_do_run()) {
					log(WARN) << ex.what();
					std::this_thread::sleep_for(std::chrono::milliseconds(error_interval_ms));
				}
				break;
			}
		}
		if(vnx_do_run())
		{
			try {
				client.open_port();
			}
			catch(const vnx::exception& ex) {
				log(WARN) << ex.value()->what;
				std::this_thread::sleep_for(std::chrono::milliseconds(error_interval_ms));
				continue;
			}
		}
	}
}

void SerialPort::signal()
{
	auto out = SocketSignal::create();
	out->port = vnx_name;
	if(m_fd >= 0) {
		out->is_open = true;
		out->is_readable = true;
		out->is_writable = true;
	} else {
		out->is_open = false;
		out->is_readable = false;
		out->is_writable = false;
	}
	publish(out, output_signals);
}

void SerialPort::print_stats()
{
	log(INFO) << (1000 * m_bytes_read) / stats_interval_ms << " B/s read, "
			<< (1000 * m_bytes_write) / stats_interval_ms << " B/s write";
	m_bytes_read = 0;
	m_bytes_write = 0;
}


} // base
} // pilot

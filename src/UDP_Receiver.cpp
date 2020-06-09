/*
 * UDP_Receiver.cpp
 *
 *  Created on: Jun 3, 2020
 *      Author: mad
 */

#include <pilot/sensors/UDP_Receiver.h>
#include <pilot/sensors/UDP_ReceiverClient.hxx>

#include <automy/basic/DataPacket.hxx>


namespace pilot {
namespace sensors {

UDP_Receiver::UDP_Receiver(const std::string& _vnx_name)
	:	UDP_ReceiverBase(_vnx_name)
{
}

void UDP_Receiver::main()
{
	std::thread read_thread;
	{
		// open a private pipe for read_loop()
		const auto module_addr = vnx::Hash64::rand();
		vnx::open_pipe(module_addr, this, UNLIMITED);
		// start read thread
		read_thread = std::thread(&UDP_Receiver::read_loop, this, module_addr);
	}

	if(stats_interval_ms) {
		set_timer_millis(stats_interval_ms, std::bind(&UDP_Receiver::print_stats, this));
	}

	Super::main();

	if(read_thread.joinable()) {
		read_thread.join();
	}
	close_port();
}

void UDP_Receiver::read_loop(const vnx::Hash64 module_addr) const noexcept
{
	UDP_ReceiverClient client(module_addr);

	while(vnx_do_run())
	{
		try {
			client.open_port();
		}
		catch(const vnx::exception& ex) {
			log(WARN) << ex.value()->what;
			std::this_thread::sleep_for(std::chrono::milliseconds(error_interval_ms));
			continue;
		}

		while(vnx_do_run())
		{
			try {
				auto sample = automy::basic::DataPacket::create();
				sample->time = vnx::get_time_micros();
				sample->payload.resize(max_packet_size);

				// read data
				const auto num_bytes = recv_packet(sample->payload.data(), sample->payload.size(), read_timeout_ms);
				if(num_bytes > 0) {
					sample->payload.resize(num_bytes);
					publish(sample, output);
					m_bytes_recv += num_bytes;
					m_packet_counter++;
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
	}
}

void UDP_Receiver::print_stats()
{
	log(INFO) << (1000 * m_packet_counter) / stats_interval_ms << " packets/s, "
			<< ((1000 * m_bytes_recv) / 1024) / stats_interval_ms << " KB/s recv";
	m_bytes_recv = 0;
	m_packet_counter = 0;
}


} // sensors
} // pilot

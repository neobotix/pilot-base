/*
 * Joystick.cpp
 *
 *  Created on: May 29, 2020
 *      Author: mad
 */

#include <pilot/base/Joystick.h>
#include <pilot/base/JoystickClient.hxx>


namespace pilot {
namespace base {

Joystick::Joystick(const std::string& _vnx_name)
	:	JoystickBase(_vnx_name)
{
}

void Joystick::main()
{
	std::thread read_thread;
	{
		// open a private pipe for read_loop()
		const auto module_addr = vnx::Hash64::rand();
		vnx::open_pipe(module_addr, this, UNLIMITED);
		// start read thread
		read_thread = std::thread(&Joystick::read_loop, this, module_addr);
	}

	if(stats_interval_ms) {
		set_timer_millis(stats_interval_ms, std::bind(&Joystick::print_stats, this));
	}

	Super::main();

	if(read_thread.joinable()) {
		read_thread.join();
	}
	close_device();
}

void Joystick::read_loop(const vnx::Hash64 module_addr) const
{
	JoystickClient client(module_addr);

	while(vnx_do_run())
	{
		try {
			client.open_device();
		}
		catch(const vnx::exception& ex) {
			log(WARN) << ex.value()->what;
			std::this_thread::sleep_for(std::chrono::milliseconds(error_interval_ms));
			continue;
		}

		JoyData data;

		while(vnx_do_run())
		{
			try {
				if(read_input(data, read_timeout_ms))
				{
					auto sample = vnx::clone(data);
					sample->time = vnx::get_time_micros();
					if(invert) {
						for(auto& value : sample->axes) {
							value *= -1;
						}
					}
					publish(sample, output);
					m_sample_counter++;
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

void Joystick::print_stats()
{
	log(INFO) << (1000 * m_sample_counter) / stats_interval_ms << " samples/s, joystick "
			<< (is_connected() ? "connected" : "lost");
	m_sample_counter = 0;
}


} // base
} // pilot

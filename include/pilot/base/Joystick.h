/*
 * Joystick.h
 *
 *  Created on: May 29, 2020
 *      Author: mad
 */

#ifndef INCLUDE_PILOT_SENSORS_JOYSTICK_H_
#define INCLUDE_PILOT_SENSORS_JOYSTICK_H_

#include <pilot/sensors/JoystickBase.hxx>
#include <pilot/JoystickData.hxx>

#include <atomic>


namespace pilot {
namespace sensors {

class Joystick : public JoystickBase {
public:
	Joystick(const std::string& _vnx_name);

protected:
	void main() override;

	void open_device() override;

	void close_device() override;

private:
	bool read_input(JoystickData& data, int timeout_ms) const;

	void read_loop(const vnx::Hash64 module_addr) const;

	void print_stats();

private:
#ifdef _WIN32
	// TODO
#else
	std::atomic<int> m_fd {-1};
	std::vector<float> axis_factors;
#endif

	mutable volatile size_t m_sample_counter = 0;

};


} // sensors
} // pilot

#endif /* INCLUDE_PILOT_SENSORS_JOYSTICK_H_ */

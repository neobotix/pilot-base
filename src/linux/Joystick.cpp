/*
 * Joystick.cpp
 *
 *  Created on: May 29, 2020
 *      Author: mad
 */

#include <pilot/base/Joystick.h>
#include <pilot/base/JoyData.hxx>

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/joystick.h>


namespace pilot {
namespace base {

void Joystick::open_device()
{
	close_device();

	m_fd = ::open(device.c_str(), O_RDONLY);
	if(m_fd < 0) {
		throw std::runtime_error("open('" + device + "') failed with: " + std::string(std::strerror(errno)));
	}
	log(INFO) << "Opened device '" << device << "'";

	axis_factors.assign(6, 1.f / 32767);
}

void Joystick::close_device()
{
	if(m_fd >= 0) {
		::close(m_fd);
		m_fd = -1;
	}
}

bool Joystick::read_input(JoyData& data, int timeout_ms) const
{
	if(m_fd < 0) {
		return false;
	}

	if(timeout_ms >= 0)
	{
		::fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(m_fd, &read_set);

		struct timeval timeout = {int32_t(timeout_ms / 1000), int32_t((timeout_ms % 1000) * 1000)};
		if(::select(m_fd + 1, &read_set, 0, 0, &timeout) < 1) {
			return false;
		}
	}

	::js_event events[256];
	const auto num_bytes = ::read(m_fd, events, sizeof(events));
	if(num_bytes < 0) {
		throw std::runtime_error("read() error: " + std::string(std::strerror(errno)));
	}
	const int num_events = num_bytes / sizeof(::js_event);

	data.axes.resize(6);
	data.buttons.resize(8);

	for(int i = 0; i < num_events; ++i)
	{
		if(events[i].type & JS_EVENT_AXIS) {
			const auto axis = events[i].number;
			if(axis >= 0 && axis < data.axes.size() && axis < axis_factors.size()) {
				data.axes[axis] = events[i].value * axis_factors[axis];
			}
		}
		if(events[i].type & JS_EVENT_BUTTON) {
			const auto button = events[i].number;
			if(button >= 0 && button < data.axes.size()) {
				data.buttons[button] = events[i].value;
			}
		}
	}
	return num_events > 0;
}


} // base
} // pilot

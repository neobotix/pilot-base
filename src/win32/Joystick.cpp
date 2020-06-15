/*
 * Joystick.cpp
 *
 *  Created on: May 29, 2020
 *      Author: mad
 */

#include <pilot/base/Joystick.h>
#include <pilot/base/JoyData.hxx>


namespace pilot {
namespace base {

void Joystick::open_device()
{
	// TODO
}

void Joystick::close_device()
{
	// TODO
}

bool Joystick::read_input(JoyData& data, int timeout_ms) const
{
	// TODO
	return false;
}

bool Joystick::is_connected(){
	// TODO
	return false;
}


} // base
} // pilot

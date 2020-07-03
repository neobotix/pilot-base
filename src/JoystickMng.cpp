/*
 * JoystickMng.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: jaw
 */

#include <pilot/base/JoystickMng.h>


namespace pilot {
namespace base {

JoystickMng::JoystickMng(const std::string& _vnx_name)
	:	JoystickMngBase(_vnx_name)
{
}

void JoystickMng::main()
{
	Super::main();
}




} // base
} // pilot

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


void JoystickMng::findJoysticks(){
	std::list<JoyParam> list = discover();
	for(JoyParam &joystick : list){
		if(!isConnected(joystick) && connect(joystick)){
			m_connectedJoysticks.push_back(joystick);
		}
	}
}


void JoystickMng::pollJoysticks(){
	auto cit = m_connectedJoysticks.cbegin();
	while(cit != m_connectedJoysticks.cend()){
		const JoyParam &joystick = *cit;
		JoyData data;
		if(poll(joystick, data)){
			cit++;
		}else{
			disconnect(joystick);
			cit = m_connectedJoysticks.erase(cit);
		}
	}
}


bool JoystickMng::isConnected(const JoyParam &joystick){
	for(const JoyParam &j : m_connectedJoysticks){
		if(compare(joystick, j)) return true;
	}
	return false;
}




} // base
} // pilot

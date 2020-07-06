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
	set_timer_millis(interval_discover_ms, std::bind(&JoystickMng::findJoysticks, this));
	set_timer_millis(interval_poll_ms, std::bind(&JoystickMng::pollJoysticks, this));

	Super::main();
}


void JoystickMng::findJoysticks(){
	std::list<JoyParam> list = discover();
	for(JoyParam &joystick : list){
		if(!isConnected(joystick) && connect(joystick)){
			JoyData data;
			Joy joy = {joystick, data};
			m_connectedJoysticks.push_back(joy);
			if(!m_active){
				m_activeJoystick = joystick;
				m_active = true;
			}
		}
	}
}


void JoystickMng::pollJoysticks(){
	auto it = m_connectedJoysticks.begin();
	while(it != m_connectedJoysticks.end()){
		Joy &joystick = *it;
		bool activeOne = m_active && compare(joystick.param, m_activeJoystick);

		ssize_t status = poll(joystick.param, joystick.data);
		if(status > 0){
			if(joystick.data.buttons[JoyData::JOYBUTTON_X] || joystick.data.buttons[JoyData::JOYBUTTON_START]){
				m_active = true;
				m_activeJoystick = joystick.param;
				activeOne = true;
			}

			if(activeOne) publish(joystick.data, output);
			it++;
		}else if(status == -1){
			if(activeOne) m_active = false;
			disconnect(joystick.param);
			it = m_connectedJoysticks.erase(it);
		}else{
			it++;
		}
	}
}


bool JoystickMng::isConnected(const JoyParam &joystick){
	for(const Joy &j : m_connectedJoysticks){
		if(compare(joystick, j.param)) return true;
	}
	return false;
}




} // base
} // pilot

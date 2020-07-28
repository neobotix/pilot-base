/*
 * JoystickMng.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: jaw
 */

#include <pilot/base/JoystickMng.h>
#include <windows.h>
#include <xinput.h>


namespace pilot {
namespace base {


std::list<JoystickMng::JoyParam> JoystickMng::discover(){
	std::list<JoystickMng::JoyParam> foundJoysticks;

	for(DWORD i=0; i<XUSER_MAX_COUNT; i++){
		XINPUT_STATE state;
		memset(&state, 0, sizeof(state));
		if(XInputGetState(i, &state) != ERROR_SUCCESS) continue;

		JoyParam joystick;
		joystick.id = i;
		foundJoysticks.push_back(joystick);
	}

	return foundJoysticks;
}


bool JoystickMng::connect(JoyParam &joystick){
	// No name retrieval supported
	joystick.description = "(Joystick at Slot " + std::to_string(joystick.id) + ")";
	XINPUT_STATE state;
	memset(&state, 0, sizeof(state));
	if(XInputGetState(joystick.id, &state) != ERROR_SUCCESS) return false;

	// limits apparently hard-coded on API side
	joystick.axesMin[JoyData::JOYAXIS_LEFT_X] = -32768;
	joystick.axesMax[JoyData::JOYAXIS_LEFT_X] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_LEFT_Y] = -32768;
	joystick.axesMax[JoyData::JOYAXIS_LEFT_Y] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_RIGHT_X] = -32768;
	joystick.axesMax[JoyData::JOYAXIS_RIGHT_X] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_RIGHT_Y] = -32768;
	joystick.axesMax[JoyData::JOYAXIS_RIGHT_Y] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_LT] = 0;
	joystick.axesMax[JoyData::JOYAXIS_LT] = 255;
	joystick.axesMin[JoyData::JOYAXIS_RT] = 0;
	joystick.axesMax[JoyData::JOYAXIS_RT] = 255;

	return true;
}


void JoystickMng::disconnect(const JoyParam &joystick){
}


ssize_t JoystickMng::poll(const JoyParam &joystick, JoyData &data){
	XINPUT_STATE state;
	memset(&state, 0, sizeof(state));
	if(XInputGetState(joystick.id, &state) != ERROR_SUCCESS) return -1;

	// if there is nothing to read we are done
	if(state.dwPacketNumber == m_packetNumber) return 0;
	ssize_t result = state.dwPacketNumber - m_packetNumber;
	m_packetNumber = state.dwPacketNumber;

	data.axes.resize(JoyData::JOYAXIS_MAX);
	data.buttons.resize(JoyData::JOYBUTTON_MAX);
	int axvalues[] = {state.Gamepad.sThumbLX,  -state.Gamepad.sThumbLY,  state.Gamepad.sThumbRX,   state.Gamepad.sThumbRY,   state.Gamepad.bLeftTrigger, state.Gamepad.bRightTrigger};
	int axjoyids[] =  {JoyData::JOYAXIS_LEFT_X, JoyData::JOYAXIS_LEFT_Y, JoyData::JOYAXIS_RIGHT_X, JoyData::JOYAXIS_RIGHT_Y, JoyData::JOYAXIS_LT,        JoyData::JOYAXIS_RT};
	for(size_t i=0; i<JoyData::JOYAXIS_MAX; i++){
		double absValue = axvalues[i];
		double relValue = 0;
		if(absValue > 0){
			relValue = absValue / joystick.axesMax[axjoyids[i]];
		}else if(absValue < 0){
			relValue = -absValue / joystick.axesMin[axjoyids[i]];
		}
		if(invert) relValue = -relValue;
		if(relValue < deadzone && relValue > -deadzone) relValue = 0;
		data.axes[axjoyids[i]] = relValue;
	}

	WORD butxids[]  = {XINPUT_GAMEPAD_A,     XINPUT_GAMEPAD_B,     XINPUT_GAMEPAD_X,     XINPUT_GAMEPAD_Y,     XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER, XINPUT_GAMEPAD_BACK,          XINPUT_GAMEPAD_START};
	int butjoyids[] = {JoyData::JOYBUTTON_A, JoyData::JOYBUTTON_B, JoyData::JOYBUTTON_X, JoyData::JOYBUTTON_Y, JoyData::JOYBUTTON_LB,        JoyData::JOYBUTTON_RB,         JoyData::JOYBUTTON_BACK,      JoyData::JOYBUTTON_START};
	for(size_t i=0; i<JoyData::JOYBUTTON_MAX; i++){
		data.buttons[butjoyids[i]] = state.Gamepad.wButtons & butxids[i];
	}

	return result;
}



bool JoystickMng::compare(const JoyParam &lhs, const JoyParam &rhs){
	return lhs.id == rhs.id;
}




} // base
} // pilot

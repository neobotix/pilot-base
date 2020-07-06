/*
 * JoystickMng.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: jaw
 */

#include <pilot/base/JoystickMng.h>
#include <vnx/Directory.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>



namespace pilot {
namespace base {


std::list<JoystickMng::JoyParam> JoystickMng::discover(){
	const std::string joydir = "/dev/input/by-path/";
	const std::string ev_suffix = "-event-joystick";
	size_t ev_suffix_length = ev_suffix.length();

	std::list<JoyParam> foundJoysticks;
	vnx::Directory dir(joydir);
	dir.open();
	std::vector<std::shared_ptr<vnx::File>> foundFiles = dir.all_files();

	for(auto f : foundFiles){
		std::string filename = f->get_name();
		if(filename == "." || filename == "..") continue;
		size_t namelength = filename.length();
		if(namelength >= ev_suffix_length && filename.find(ev_suffix, namelength-ev_suffix_length) != std::string::npos){
			// joystick found
			std::string interface = joydir+filename;

			JoyParam joystick;
			joystick.interface = interface;
			foundJoysticks.push_back(joystick);
		}
	}
	dir.close();

	return foundJoysticks;
}


bool JoystickMng::connect(JoyParam &joystick){
	int fd = open(joystick.interface.c_str(), O_RDWR);
	if(fd == -1) return false;
	joystick.fd = fd;

	char name[128];
	if(ioctl(fd, EVIOCGNAME(sizeof(name)), name) < 0){
		strncpy(name, "(Unknown Joystick)", 19);
	}
	joystick.description = name;


	// default values, just in case
	joystick.axesMin[JoyData::JOYAXIS_LEFT_X] = -32767;
	joystick.axesMax[JoyData::JOYAXIS_LEFT_X] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_LEFT_Y] = -32767;
	joystick.axesMax[JoyData::JOYAXIS_LEFT_Y] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_RIGHT_X] = -32767;
	joystick.axesMax[JoyData::JOYAXIS_RIGHT_X] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_RIGHT_Y] = -32767;
	joystick.axesMax[JoyData::JOYAXIS_RIGHT_Y] = 32767;
	joystick.axesMin[JoyData::JOYAXIS_LT] = 0;
	joystick.axesMax[JoyData::JOYAXIS_LT] = 255;
	joystick.axesMin[JoyData::JOYAXIS_RT] = 0;
	joystick.axesMax[JoyData::JOYAXIS_RT] = 255;

	// mapping evdev constants to our constants
	int evdevcode[] = {ABS_X,                   ABS_Y,                   ABS_RX,                   ABS_RY,                   ABS_Z,               ABS_RZ};
	int axiscode[]  = {JoyData::JOYAXIS_LEFT_X, JoyData::JOYAXIS_LEFT_Y, JoyData::JOYAXIS_RIGHT_X, JoyData::JOYAXIS_RIGHT_Y, JoyData::JOYAXIS_LT, JoyData::JOYAXIS_RT};
	input_absinfo absinfo;
	for(int i=0; i<JoyData::JOYAXIS_MAX; i++){
		if(ioctl(fd, EVIOCGABS(evdevcode[i]), &absinfo) >= 0){
			joystick.axesMin[axiscode[i]] = absinfo.minimum;
			joystick.axesMax[axiscode[i]] = absinfo.maximum;
		}
	}

	return true;
}


void JoystickMng::disconnect(const JoyParam &joystick){
	::close(joystick.fd);
}


ssize_t JoystickMng::poll(const JoyParam &joystick, JoyData &data){
	fd_set fdset;
	timeval tv = {0, 0};
	FD_ZERO(&fdset);
	FD_SET(joystick.fd, &fdset);

	int ret = ::select(joystick.fd+1, &fdset, NULL, NULL, &tv);
	if(ret < 0){
		// error
		return -1;
	}else if(ret == 0){
		// nothing to read, but that is not an error
		//resetValues(joystick);
		return 0;
	}

	input_event js[256];
	ssize_t len = ::read(joystick.fd, js, sizeof(js));
	if(len == -1) return -1;


	size_t numEvents = len / sizeof(input_event);

	int targetAxis = JoyData::JOYAXIS_MAX;
	int targetButton = JoyData::JOYBUTTON_MAX;
	data.axes.resize(JoyData::JOYAXIS_MAX);
	data.buttons.resize(JoyData::JOYBUTTON_MAX);
	for (size_t i=0; i < numEvents; i++){
		switch (js[i].type){
		case EV_ABS:
			// Axes
			switch(js[i].code){
			case ABS_X:
				targetAxis = JoyData::JOYAXIS_LEFT_X;
				break;
			case ABS_Y:
				targetAxis = JoyData::JOYAXIS_LEFT_Y;
				break;
			case ABS_RX:
				targetAxis = JoyData::JOYAXIS_RIGHT_X;
				break;
			case ABS_RY:
				targetAxis = JoyData::JOYAXIS_RIGHT_Y;
				break;
			case ABS_Z:
				targetAxis = JoyData::JOYAXIS_LT;
				break;
			case ABS_RZ:
				targetAxis = JoyData::JOYAXIS_RT;
				break;
			}
			if(targetAxis != JoyData::JOYAXIS_MAX){
				double absValue = js[i].value;
				double relValue = 0;
				if(absValue > 0){
					relValue = absValue / joystick.axesMax[targetAxis];
				}else if(absValue < 0){
					relValue = -absValue / joystick.axesMin[targetAxis];
				}
				data.axes[targetAxis] = relValue;
			}

			break;
		case EV_KEY:
			// Buttons
			switch(js[i].code){
			case BTN_A:
				targetButton = JoyData::JOYBUTTON_A;
				break;
			case BTN_B:
				targetButton = JoyData::JOYBUTTON_B;
				break;
			case BTN_X:
				targetButton = JoyData::JOYBUTTON_X;
				break;
			case BTN_Y:
				targetButton = JoyData::JOYBUTTON_Y;
				break;
			case BTN_TL:
				targetButton = JoyData::JOYBUTTON_LB;
				break;
			case BTN_TR:
				targetButton = JoyData::JOYBUTTON_RB;
				break;
			case BTN_SELECT:
				targetButton = JoyData::JOYBUTTON_BACK;
				break;
			case BTN_START:
				targetButton = JoyData::JOYBUTTON_START;
				break;
			}
			if(targetButton != JoyData::JOYBUTTON_MAX){
				data.buttons[targetButton] = (js[i].value != 0);
			}

			break;
		}
	}

	return numEvents;
}



bool JoystickMng::compare(const JoyParam &lhs, const JoyParam &rhs){
	return lhs.interface == rhs.interface;
}



} // base
} // pilot

/*
 * JoystickMng.h
 *
 *  Created on: Jul 3, 2020
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_JOYSTICKMNG_H_
#define INCLUDE_PILOT_BASE_JOYSTICKMNG_H_

#include <pilot/base/JoystickMngBase.hxx>
#include <pilot/base/JoyData.hxx>
#include <string>
#include <list>



namespace pilot {
namespace base {

class JoystickMng : public JoystickMngBase {
public:
	JoystickMng(const std::string &_vnx_name);

protected:
	struct JoyParam{
#ifdef _WIN32
		int id;
#else
		std::string interface;
		int fd;
#endif
		std::string description;
		int axesMin[JoyData::JOYAXIS_MAX];
		int axesMax[JoyData::JOYAXIS_MAX];
	};

	void main() override;

private:
	std::list<JoyParam> m_connectedJoysticks;

	void findJoysticks();
	void pollJoysticks();
	bool isConnected(const JoyParam &joystick);

	std::list<JoyParam> discover();
	bool connect(JoyParam &joystick);
	void disconnect(const JoyParam &joystick);
	bool poll(const JoyParam &joystick, JoyData &data);
	bool compare(const JoyParam &lhs, const JoyParam &rhs);

};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_JOYSTICKMNG_H_ */

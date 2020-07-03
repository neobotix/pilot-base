/*
 * JoystickMng.h
 *
 *  Created on: Jul 3, 2020
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_JOYSTICKMNG_H_
#define INCLUDE_PILOT_BASE_JOYSTICKMNG_H_

#include <pilot/base/JoystickMngBase.hxx>



namespace pilot {
namespace base {

class JoystickMng : public JoystickMngBase {
public:
	JoystickMng(const std::string& _vnx_name);

protected:
	void main() override;

};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_JOYSTICKMNG_H_ */

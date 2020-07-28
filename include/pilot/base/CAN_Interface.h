/*
 * CAN_Interface.h
 *
 *  Created on: Jul 27, 2020
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_CAN_INTERFACE_H_
#define INCLUDE_PILOT_BASE_CAN_INTERFACE_H_

#include <pilot/base/CAN_Frame.hxx>


namespace pilot {
namespace base {

class CAN_Interface {
public:

	virtual ~CAN_Interface() = default;

	virtual void close() = 0;

	virtual bool read(CAN_Frame &frame, int timeout_ms) = 0;

	virtual void write(const CAN_Frame& frame) = 0;

};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_INTERFACE_H_ */

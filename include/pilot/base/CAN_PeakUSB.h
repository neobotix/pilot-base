/*
 * CAN_PeakUSB.h
 *
 *  Created on: Jul 27, 2020
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_CAN_PEAKUSB_H_
#define INCLUDE_PILOT_BASE_CAN_PEAKUSB_H_

#include <pilot/base/CAN_Frame.hxx>
#include <pilot/base/CAN_Interface.h>

#include <windows.h>
#include <pcanbasic/PCANBasic.h>


namespace pilot {
namespace base {

class CAN_PeakUSB : public CAN_Interface {
public:
	CAN_PeakUSB(int channel, int baud_rate, const socketcan_options_t &socket_options);

	void close() override;

	bool read(CAN_Frame &frame, int timeout_ms) override;

	void write(const CAN_Frame& frame) override;

private:
	using f_CAN_Initialize = decltype(CAN_Initialize);
	using f_CAN_Read = decltype(CAN_Read);
	using f_CAN_Write = decltype(CAN_Write);
	using f_CAN_Uninitialize = decltype(CAN_Uninitialize);
	using f_CAN_SetValue = decltype(CAN_SetValue);
	using f_CAN_FilterMessages = decltype(CAN_FilterMessages);
	using f_CAN_GetErrorText = decltype(CAN_GetErrorText);

	f_CAN_Initialize *p_CAN_Initialize;
	f_CAN_Read *p_CAN_Read;
	f_CAN_Write *p_CAN_Write;
	f_CAN_Uninitialize *p_CAN_Uninitialize;
	f_CAN_SetValue *p_CAN_SetValue;
	f_CAN_FilterMessages *p_CAN_FilterMessages;
	f_CAN_GetErrorText *p_CAN_GetErrorText;

	TPCANHandle pcan_interface;
	HANDLE m_event_read;

	std::string get_error_text(const TPCANStatus &status) const;
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_PEAKUSB_H_ */

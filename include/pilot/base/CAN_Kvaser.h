/*
 * CAN_Kvaser.h
 *
 *  Created on: Feb 26, 2026
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_CAN_KVASER_H_
#define INCLUDE_PILOT_BASE_CAN_KVASER_H_

#include <pilot/base/CAN_Frame.hxx>
#include <pilot/base/CAN_Interface.h>

#include <canlib/canlib.h>


namespace pilot {
namespace base {


class CAN_Kvaser : public CAN_Interface {
public:
	CAN_Kvaser(int channel, int bitrate, const socketcan_options_t &options);

	void close() override;
	bool read(CAN_Frame &frame, int timeout_ms) override;
	void write(const CAN_Frame &frame) override;

private:
	using f_canInitializeLibrary = decltype(canInitializeLibrary);
	using f_canOpenChannel = decltype(canOpenChannel);
	using f_canSetBusParams = decltype(canSetBusParams);
	using f_canIoCtl = decltype(canIoCtl);
	using f_canBusOn = decltype(canBusOn);
	using f_canBusOff = decltype(canBusOff);
	using f_canClose = decltype(canClose);
	using f_canReadWait = decltype(canReadWait);
	using f_canWrite = decltype(canWrite);
	using f_canReadErrorCounters = decltype(canReadErrorCounters);
	using f_canGetErrorText = decltype(canGetErrorText);

	f_canInitializeLibrary *p_canInitializeLibrary;
	f_canOpenChannel *p_canOpenChannel;
	f_canSetBusParams *p_canSetBusParams;
	f_canIoCtl *p_canIoCtl;
	f_canBusOn *p_canBusOn;
	f_canBusOff *p_canBusOff;
	f_canClose *p_canClose;
	f_canReadWait *p_canReadWait;
	f_canWrite *p_canWrite;
	f_canReadErrorCounters *p_canReadErrorCounters;
	f_canGetErrorText *p_canGetErrorText;

	canHandle handle;

	std::string get_error_text(canStatus status) const;
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_KVASER_H_ */

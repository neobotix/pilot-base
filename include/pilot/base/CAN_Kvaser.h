/*
 * CAN_Kvaser.h
 *
 *  Created on: Mar 04, 2026
 */

#ifndef INCLUDE_PILOT_BASE_CAN_KVASER_H_
#define INCLUDE_PILOT_BASE_CAN_KVASER_H_

#include <pilot/base/CAN_Frame.hxx>
#include <pilot/base/CAN_Interface.h>
#include <windows.h>
#include <canlib/canlib.h>

#include <string>


namespace pilot {
namespace base {

class CAN_Kvaser : public CAN_Interface {
public:
	CAN_Kvaser(int channel, int baud_rate, const socketcan_options_t &socket_options);

	~CAN_Kvaser();

	void close() override;

	bool read(CAN_Frame &frame, int timeout_ms) override;

	void write(const CAN_Frame& frame) override;

private:
	template<typename T>
	static T* resolve(HINSTANCE dll, const char* name);

	using fcanInitializeLibrary = decltype(canInitializeLibrary);
	using fcanOpenChannel = decltype(canOpenChannel);
	using fcanSetBusParams = decltype(canSetBusParams);
	using fcanBusOn = decltype(canBusOn);
	using fcanBusOff = decltype(canBusOff);
	using fcanClose = decltype(canClose);
	using fcanWrite = decltype(canWrite);
	using fcanReadWait = decltype(canReadWait);
	using fcanGetErrorText = decltype(canGetErrorText);
	using fcanReadErrorCounters = decltype(canReadErrorCounters);
	using fcanIoCtl = decltype(canIoCtl);

	fcanBusOff* pfcanBusOff;
	fcanClose* pfcanClose;
	fcanWrite* pfcanWrite;
	fcanReadWait* pfcanReadWait;
	fcanGetErrorText* pfcanGetErrorText;
	fcanReadErrorCounters* pfcanReadErrorCounters;
	fcanIoCtl* pfcanIoCtl;

	CanHandle m_handle = canINVALID_HANDLE;

	std::string get_error_text(canStatus status) const;
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_KVASER_H_ */

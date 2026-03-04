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
	CAN_Kvaser(int baud_rate, const socketcan_options_t &socket_options);

	~CAN_Kvaser();

	void close() override;

	bool read(CAN_Frame &frame, int timeout_ms) override;

	void write(const CAN_Frame& frame) override;

private:
	typedef void(__stdcall fcanInitializeLibrary)(void);
	typedef CanHandle(__stdcall fcanOpenChannel)(int channel, int flags);
	typedef canStatus(__stdcall fcanSetBusParams)(const CanHandle hnd, long freq, unsigned int tseg1, unsigned int tseg2, unsigned int sjw, unsigned int noSamp, unsigned int syncmode);
	typedef canStatus(__stdcall fcanBusOn)(const CanHandle hnd);
	typedef canStatus(__stdcall fcanBusOff)(const CanHandle hnd);
	typedef canStatus(__stdcall fcanClose)(const CanHandle hnd);
	typedef canStatus(__stdcall fcanWrite)(const CanHandle hnd, long id, void *msg, unsigned int dlc, unsigned int flag);
	typedef canStatus(__stdcall fcanReadWait)(const CanHandle hnd, long *id, void *msg, unsigned int *dlc, unsigned int *flag, unsigned long *time, unsigned long timeout);
	typedef canStatus(__stdcall fcanGetErrorText)(canStatus err, char *buf, unsigned int bufsiz);
	typedef canStatus(__stdcall fcanReadErrorCounters)(const CanHandle hnd, unsigned int *txErr, unsigned int *rxErr, unsigned int *ovErr);

	fcanInitializeLibrary* pfcanInitializeLibrary;
	fcanOpenChannel* pfcanOpenChannel;
	fcanSetBusParams* pfcanSetBusParams;
	fcanBusOn* pfcanBusOn;
	fcanBusOff* pfcanBusOff;
	fcanClose* pfcanClose;
	fcanWrite* pfcanWrite;
	fcanReadWait* pfcanReadWait;
	fcanGetErrorText* pfcanGetErrorText;
	fcanReadErrorCounters* pfcanReadErrorCounters;

	CanHandle m_handle = canINVALID_HANDLE;
	HINSTANCE m_hInstance;
	bool m_initialized = false;

	std::string get_error_text(canStatus status) const;
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_KVASER_H_ */

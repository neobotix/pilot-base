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
	CAN_PeakUSB(int baud_rate);

	~CAN_PeakUSB();

	void close();

	bool read(CAN_Frame &frame, int timeout_ms);

	void write(const CAN_Frame& frame);

private:
	typedef TPCANStatus(__stdcall fCAN_Init)(TPCANHandle, TPCANBaudrate, TPCANType, DWORD, WORD);
	typedef TPCANStatus(__stdcall fCAN_InitFD)(TPCANHandle, TPCANBitrateFD);
	typedef TPCANStatus(__stdcall fCAN_Read)(TPCANHandle, TPCANMsg*, TPCANTimestamp*);
	typedef TPCANStatus(__stdcall fCAN_Write)(TPCANHandle, TPCANMsg*);
	typedef TPCANStatus(__stdcall fCAN_Close)(TPCANHandle);
	typedef TPCANStatus(__stdcall fCAN_Reset)(TPCANHandle);
	typedef TPCANStatus(__stdcall fCAN_Status)(TPCANHandle);
	//typedef TPCANStatus(__stdcall fCAN_GetErrorText)(TPCANStatus, WORD, LPSTR);

	fCAN_Init* pfCAN_Init;
	fCAN_InitFD* pfCAN_InitFD;
	fCAN_Write* pfCAN_Write;
	fCAN_Read* pfCAN_Read;
	fCAN_Close* pfCAN_Close;
	fCAN_Status* pfCAN_Status;
	fCAN_Reset* pfCAN_Reset;
	//fCAN_GetErrorText* pfCAN_GetErrorText;

	TPCANHandle m_pcanHandle;
	HINSTANCE m_hInstance;
	bool m_initialized = false;
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_CAN_PEAKUSB_H_ */

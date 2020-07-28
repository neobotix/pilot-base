/*
 * CAN_PeakUSB.cpp
 *
 *  Created on: Jul 27, 2020
 *      Author: jaw
 */

#include <pilot/base/CAN_PeakUSB.h>
#include <windows.h>



namespace pilot {
namespace base {


CAN_PeakUSB::CAN_PeakUSB(int baud_rate){
	m_hInstance = LoadLibrary("PCANBasic");

	if (m_hInstance == NULL){
		throw std::runtime_error("Dynamic library 'PCANBasic.dll' can't be loaded");
	}

	pfCAN_Init = (fCAN_Init*)GetProcAddress(m_hInstance, "CAN_Initialize");
	pfCAN_Write = (fCAN_Write*)GetProcAddress(m_hInstance, "CAN_Write");
	pfCAN_Read = (fCAN_Read*)GetProcAddress(m_hInstance, "CAN_Read");
	pfCAN_Close = (fCAN_Close*)GetProcAddress(m_hInstance, "CAN_Uninitialize");
	pfCAN_Reset = (fCAN_Reset*)GetProcAddress(m_hInstance, "CAN_Reset");
	pfCAN_Status = (fCAN_Status*)GetProcAddress(m_hInstance, "CAN_GetStatus");
	pfCAN_InitFD = (fCAN_InitFD*)GetProcAddress(m_hInstance, "CAN_InitializeFD");
	//pfCAN_GetErrorText = (fCAN_GetErrorText*)GetProcAddress(hInstance, "CAN_GetErrorText");


	int ret = PCAN_ERROR_OK;

	m_pcanHandle = TPCANHandle(PCAN_USBBUS1);

	switch(baud_rate){
	case 1000000:
		ret = pfCAN_Init(m_pcanHandle, PCAN_BAUD_1M,0,0,0);
		break;

	case 500000:
		ret = pfCAN_Init(m_pcanHandle, PCAN_BAUD_500K, 0, 0, 0);
		//ret = pfCAN_Init(m_pcanHandle, PCAN_BAUD_500K);
		break;

	case 250000:
		ret = pfCAN_Init(m_pcanHandle, PCAN_BAUD_250K,0,0,0);
		break;

	default:
		throw std::runtime_error("Baud rate not supported");
	}

	if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN initialization error: " + std::to_string(ret));
	}

	m_initialized = true;
}


CAN_PeakUSB::~CAN_PeakUSB(){
	if(!m_initialized) close();
}


void CAN_PeakUSB::close(){
	pfCAN_Close(m_pcanHandle);
	m_initialized = false;
}

bool CAN_PeakUSB::read(CAN_Frame &frame){
	TPCANMsg TPCMsg;
	TPCMsg.LEN = 8;
	TPCMsg.MSGTYPE = 0;
	TPCMsg.ID = 0;

	int ret = pfCAN_Read(m_pcanHandle, &TPCMsg, NULL);
	if (ret == PCAN_ERROR_QRCVEMPTY || TPCMsg.MSGTYPE == PCAN_MESSAGE_STATUS){
		return false;
	}


	frame.time = vnx::get_time_micros();
	frame.id = TPCMsg.ID;
	frame.size = TPCMsg.LEN;
	for(size_t i=0; i<8; i++){
		frame.data[i] = TPCMsg.DATA[i];
	}

	return true;
}

void CAN_PeakUSB::write(const CAN_Frame& frame){
	TPCANMsg TPCMsg;


	TPCMsg.LEN = frame.size;
	TPCMsg.ID = frame.id;
	TPCMsg.MSGTYPE = 0;
	for(size_t i=0; i<8; i++)
		TPCMsg.DATA[i] = frame.data[i];

	pfCAN_Write(m_pcanHandle, &TPCMsg);
	pfCAN_Status(m_pcanHandle);
}



} // base
} // pilot

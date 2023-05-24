/*
 * CAN_PeakUSB.cpp
 *
 *  Created on: Jul 27, 2020
 *      Author: jaw
 */

#include <pilot/base/CAN_PeakUSB.h>
#include <vnx/Time.h>

#include <thread>
#include <chrono>


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
	pfCAN_SetValue = (fCAN_SetValue*)GetProcAddress(m_hInstance, "CAN_SetValue");
	pfCAN_GetErrorText = (fCAN_GetErrorText*)GetProcAddress(m_hInstance, "CAN_GetErrorText");


	int ret = PCAN_ERROR_OK;

	m_pcanHandle = TPCANHandle(PCAN_USBBUS1);

	switch(baud_rate){
	case 1000000:
		ret = pfCAN_Init(m_pcanHandle, PCAN_BAUD_1M,0,0,0);
		break;

	case 500000:
		ret = pfCAN_Init(m_pcanHandle, PCAN_BAUD_500K, 0, 0, 0);
		break;

	case 250000:
		ret = pfCAN_Init(m_pcanHandle, PCAN_BAUD_250K,0,0,0);
		break;

	default:
		throw std::runtime_error("Baud rate not supported");
	}

	if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN initialization error: " + get_error_text(ret));
	}

	m_event_read = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(m_event_read == NULL){
		throw std::runtime_error("CreateEvent() failed with:" + std::to_string(GetLastError()));
	}
	ret = pfCAN_SetValue(m_pcanHandle, PCAN_RECEIVE_EVENT, &m_event_read, sizeof(m_event_read));
	if(ret != PCAN_ERROR_OK){
		CloseHandle(m_event_read);
		m_event_read = NULL;
		throw std::runtime_error("Setting of event handle failed with: " + get_error_text(ret));
	}

	m_initialized = true;
}


CAN_PeakUSB::~CAN_PeakUSB(){
	if(m_initialized) close();
}


void CAN_PeakUSB::close(){
	if(m_initialized){
		pfCAN_Close(m_pcanHandle);
		CloseHandle(m_event_read);
	}
	m_initialized = false;
}

bool CAN_PeakUSB::read(CAN_Frame &frame, int timeout_ms){
	if(!m_initialized){
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));
		return false;
	}

	TPCANMsg TPCMsg;
	TPCMsg.LEN = 8;
	TPCMsg.MSGTYPE = 0;
	TPCMsg.ID = 0;

	TPCANStatus ret = pfCAN_Read(m_pcanHandle, &TPCMsg, NULL);
	if(ret == PCAN_ERROR_QRCVEMPTY && WaitForSingleObject(m_event_read, timeout_ms) != WAIT_TIMEOUT){
		ret = pfCAN_Read(m_pcanHandle, &TPCMsg, NULL);
	}
	if(ret == PCAN_ERROR_QRCVEMPTY){
		return false;
	}else if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN_Read() failed with: " + get_error_text(ret));
	}

	switch(TPCMsg.MSGTYPE) {
		case PCAN_MESSAGE_STANDARD:
		case PCAN_MESSAGE_EXTENDED:
			frame.time = vnx::get_time_micros();
			frame.id = TPCMsg.ID;
			frame.size = TPCMsg.LEN;
			for(size_t i=0; i<8; i++){
				frame.data[i] = TPCMsg.DATA[i];
			}
			return true;
	}
	return false;
}

void CAN_PeakUSB::write(const CAN_Frame& frame){
	if(!m_initialized) return;

	TPCANMsg TPCMsg;

	TPCMsg.LEN = frame.size;
	TPCMsg.ID = frame.id;
	if(frame.id > 2047){
		TPCMsg.MSGTYPE = PCAN_MESSAGE_EXTENDED;
	}else{
		TPCMsg.MSGTYPE = PCAN_MESSAGE_STANDARD;
	}
	for(size_t i=0; i<8; i++){
		TPCMsg.DATA[i] = frame.data[i];
	}

	const TPCANStatus ret = pfCAN_Write(m_pcanHandle, &TPCMsg);
	if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN_Write() failed with: " + get_error_text(ret));
	}
}


std::string CAN_PeakUSB::get_error_text(const TPCANStatus &status) const{
	// Maximum length is 255 characters, according to the docs.
	char str[256];
	const WORD language = 0;
	std::string result;

	const TPCANStatus ret = pfCAN_GetErrorText(status, language, str);
	if(ret != PCAN_ERROR_OK){
		result = "Code " + std::to_string(status) + " (getting error text failed with Code " + std::to_string(ret) + ")";
	}else{
		result = str;
	}
	return result;
}



} // base
} // pilot

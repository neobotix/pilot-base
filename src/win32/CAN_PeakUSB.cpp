/*
 * CAN_PeakUSB.cpp
 *
 *  Created on: Jul 27, 2020
 *      Author: jaw
 */

#include <pilot/base/CAN_PeakUSB.h>
#include <pilot/base/socketcan_options_t.hxx>
#include <vnx/Time.h>

#include <thread>
#include <chrono>


namespace pilot {
namespace base {


template<class T>
T *get_proc(HMODULE dll, const std::string &name){
	T *result = reinterpret_cast<T *>(GetProcAddress(dll, name.c_str()));
	if(!result){
		throw std::runtime_error("Failed to get address of " + name);
	}
	return result;
}


CAN_PeakUSB::CAN_PeakUSB(int channel, int baud_rate, const socketcan_options_t &socket_options){
	const std::string libname = "PCANBasic";
	const auto dll = LoadLibrary(libname.c_str());
	if(!dll){
		throw std::runtime_error("Dynamic library " + libname + " could not be loaded");
	}

	p_CAN_Initialize = get_proc<f_CAN_Initialize>(dll, "CAN_Initialize");
	p_CAN_Write = get_proc<f_CAN_Write>(dll, "CAN_Write");
	p_CAN_Read = get_proc<f_CAN_Read>(dll, "CAN_Read");
	p_CAN_Uninitialize = get_proc<f_CAN_Uninitialize>(dll, "CAN_Uninitialize");
	p_CAN_SetValue = get_proc<f_CAN_SetValue>(dll, "CAN_SetValue");
	p_CAN_FilterMessages = get_proc<f_CAN_FilterMessages>(dll, "CAN_FilterMessages");
	p_CAN_GetErrorText = get_proc<f_CAN_GetErrorText>(dll, "CAN_GetErrorText");

	pcan_interface = channel;

	TPCANBaudrate freq;
	switch(baud_rate){
	case 1000000: freq = PCAN_BAUD_1M; break;
	case 800000: freq = PCAN_BAUD_800K; break;
	case 500000: freq = PCAN_BAUD_500K; break;
	case 250000: freq = PCAN_BAUD_250K; break;
	case 125000: freq = PCAN_BAUD_125K; break;
	case 100000: freq = PCAN_BAUD_100K; break;
	case 95238: freq = PCAN_BAUD_95K; break;
	case 83333: freq = PCAN_BAUD_83K; break;
	case 50000: freq = PCAN_BAUD_50K; break;
	case 47619: freq = PCAN_BAUD_47K; break;
	case 33333: freq = PCAN_BAUD_33K; break;
	case 20000: freq = PCAN_BAUD_20K; break;
	case 10000: freq = PCAN_BAUD_10K; break;
	case 5000: freq = PCAN_BAUD_5K; break;
	default:
		throw std::runtime_error("Baud rate not supported");
	}

	TPCANStatus ret;
	ret = p_CAN_Initialize(pcan_interface, freq, 0, 0, 0);
	if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN_Initialize() failed with: " + get_error_text(ret));
	}

	m_event_read = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(m_event_read == NULL){
		throw std::runtime_error("CreateEvent() failed with: " + std::to_string(GetLastError()));
	}
	ret = p_CAN_SetValue(pcan_interface, PCAN_RECEIVE_EVENT, &m_event_read, sizeof(m_event_read));
	if(ret != PCAN_ERROR_OK){
		CloseHandle(m_event_read);
		throw std::runtime_error("CAN_SetValue(PCAN_RECEIVE_EVENT) failed with: " + get_error_text(ret));
	}

	bool receive_errors = socket_options.receive_error_frames;
	ret = p_CAN_SetValue(pcan_interface, PCAN_ALLOW_ERROR_FRAMES, &receive_errors, sizeof(receive_errors));
	if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN_SetValue(PCAN_ALLOW_ERROR_FRAMES) failed with: " + get_error_text(ret));
	}

	// TODO: CAN_FilterMessages() with socket_options.filter_list ?
}


void CAN_PeakUSB::close(){
	p_CAN_Uninitialize(pcan_interface);
	CloseHandle(m_event_read);
}

bool CAN_PeakUSB::read(CAN_Frame &frame, int timeout_ms){
	TPCANMsg message;
	TPCANStatus ret = p_CAN_Read(pcan_interface, &message, NULL);
	if(ret == PCAN_ERROR_QRCVEMPTY && WaitForSingleObject(m_event_read, timeout_ms) != WAIT_TIMEOUT){
		ret = p_CAN_Read(pcan_interface, &message, NULL);
	}
	if(ret == PCAN_ERROR_QRCVEMPTY || (message.MSGTYPE != PCAN_MESSAGE_STANDARD && message.MSGTYPE != PCAN_MESSAGE_EXTENDED && message.MSGTYPE != PCAN_MESSAGE_ERRFRAME)){
		return false;
	}else if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN_Read() failed with: " + get_error_text(ret));
	}

	frame.time = vnx::get_time_micros();
	frame.id = message.ID;
	frame.size = message.LEN;
	for(size_t i=0; i<frame.size; i++){
		frame.data[i] = message.DATA[i];
	}

	if(message.MSGTYPE == PCAN_MESSAGE_ERRFRAME){
		can_error_t error;
		if(frame.id == 1 || frame.id == 2 || frame.id == 4){
			error.error_classes.insert(can_error_class_e::PROTOCOL);
		}
		if(frame.id == 8){
			// "Other type of error"
			error.error_classes.insert(can_error_class_e::PROTOCOL);
		}
		error.num_rx_errors = message.DATA[2];
		error.num_tx_errors = message.DATA[3];
		frame.error = error;
	}

	return true;
}

void CAN_PeakUSB::write(const CAN_Frame& frame){
	TPCANMsg message;
	message.LEN = frame.size;
	message.ID = frame.id;
	if(frame.id > 2047){
		message.MSGTYPE = PCAN_MESSAGE_EXTENDED;
	}else{
		message.MSGTYPE = PCAN_MESSAGE_STANDARD;
	}
	for(size_t i=0; i<frame.size; i++){
		message.DATA[i] = frame.data[i];
	}

	const TPCANStatus ret = p_CAN_Write(pcan_interface, &message);
	if(ret != PCAN_ERROR_OK){
		throw std::runtime_error("CAN_Write() failed with: " + get_error_text(ret));
	}
}


std::string CAN_PeakUSB::get_error_text(const TPCANStatus &status) const{
	// Maximum length is 255 characters, according to the docs.
	char str[256];
	const WORD language = 0;
	std::string result;

	const TPCANStatus ret = p_CAN_GetErrorText(status, language, str);
	if(ret != PCAN_ERROR_OK){
		result = "Code " + std::to_string(status) + " (getting error text failed with Code " + std::to_string(ret) + ")";
	}else{
		result = str;
	}
	return result;
}



} // base
} // pilot

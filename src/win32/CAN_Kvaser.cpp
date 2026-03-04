/*
 * CAN_Kvaser.cpp
 *
 *  Created on: Mar 04, 2026
 */

#include <pilot/base/CAN_Kvaser.h>
#include <pilot/base/socketcan_options_t.hxx>
#include <vnx/Time.h>

#include <thread>
#include <chrono>


namespace pilot {
namespace base {


CAN_Kvaser::CAN_Kvaser(int baud_rate, const socketcan_options_t &socket_options){
	m_hInstance = LoadLibrary("canlib32");

	if(m_hInstance == NULL){
		throw std::runtime_error("Dynamic library 'canlib32.dll' can't be loaded");
	}

	pfcanInitializeLibrary = (fcanInitializeLibrary*)GetProcAddress(m_hInstance, "canInitializeLibrary");
	pfcanOpenChannel = (fcanOpenChannel*)GetProcAddress(m_hInstance, "canOpenChannel");
	pfcanSetBusParams = (fcanSetBusParams*)GetProcAddress(m_hInstance, "canSetBusParams");
	pfcanBusOn = (fcanBusOn*)GetProcAddress(m_hInstance, "canBusOn");
	pfcanBusOff = (fcanBusOff*)GetProcAddress(m_hInstance, "canBusOff");
	pfcanClose = (fcanClose*)GetProcAddress(m_hInstance, "canClose");
	pfcanWrite = (fcanWrite*)GetProcAddress(m_hInstance, "canWrite");
	pfcanReadWait = (fcanReadWait*)GetProcAddress(m_hInstance, "canReadWait");
	pfcanGetErrorText = (fcanGetErrorText*)GetProcAddress(m_hInstance, "canGetErrorText");
	pfcanReadErrorCounters = (fcanReadErrorCounters*)GetProcAddress(m_hInstance, "canReadErrorCounters");

	pfcanInitializeLibrary();

	m_handle = pfcanOpenChannel(0, canOPEN_ACCEPT_VIRTUAL);
	if(m_handle < 0){
		throw std::runtime_error("canOpenChannel() failed with: " + get_error_text(canStatus(m_handle)));
	}

	canStatus ret = canOK;

	switch(baud_rate){
	case 1000000:
		ret = pfcanSetBusParams(m_handle, canBITRATE_1M, 0, 0, 0, 0, 0);
		break;

	case 500000:
		ret = pfcanSetBusParams(m_handle, canBITRATE_500K, 0, 0, 0, 0, 0);
		break;

	case 250000:
		ret = pfcanSetBusParams(m_handle, canBITRATE_250K, 0, 0, 0, 0, 0);
		break;

	default:
		throw std::runtime_error("Baud rate not supported");
	}

	if(ret != canOK){
		throw std::runtime_error("canSetBusParams() failed with: " + get_error_text(ret));
	}

	ret = pfcanBusOn(m_handle);
	if(ret != canOK){
		throw std::runtime_error("canBusOn() failed with: " + get_error_text(ret));
	}

	m_initialized = true;
}


CAN_Kvaser::~CAN_Kvaser(){
	if(m_initialized) close();
}


void CAN_Kvaser::close(){
	if(m_initialized){
		pfcanBusOff(m_handle);
		pfcanClose(m_handle);
	}
	m_initialized = false;
}

bool CAN_Kvaser::read(CAN_Frame &frame, int timeout_ms){
	if(!m_initialized){
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));
		return false;
	}

	long id = 0;
	unsigned char msg[8] = {};
	unsigned int dlc = 0;
	unsigned int flag = 0;
	unsigned long timestamp = 0;

	const canStatus ret = pfcanReadWait(m_handle, &id, msg, &dlc, &flag, &timestamp, (unsigned long)timeout_ms);
	if(ret == canERR_NOMSG || ret == canERR_TIMEOUT){
		return false;
	}else if(ret != canOK){
		throw std::runtime_error("canReadWait() failed with: " + get_error_text(ret));
	}

	bool received = false;
	if(flag & canMSG_ERROR_FRAME){
		frame.time = vnx::get_time_micros();
		frame.id = id;
		frame.size = dlc;
		for(size_t i = 0; i < 8; i++){
			frame.data[i] = msg[i];
		}

		can_error_t error;
		error.error_classes.insert(can_error_class_e::PROTOCOL);

		unsigned int txErr = 0;
		unsigned int rxErr = 0;
		unsigned int ovErr = 0;
		if(pfcanReadErrorCounters(m_handle, &txErr, &rxErr, &ovErr) == canOK){
			error.num_tx_errors = txErr;
			error.num_rx_errors = rxErr;
		}
		frame.error = error;
		received = true;
	}else if((flag & canMSG_STD) || (flag & canMSG_EXT)){
		frame.time = vnx::get_time_micros();
		frame.id = id;
		frame.size = dlc;
		for(size_t i = 0; i < 8; i++){
			frame.data[i] = msg[i];
		}
		received = true;
	}

	return received;
}

void CAN_Kvaser::write(const CAN_Frame& frame){
	if(!m_initialized) return;

	unsigned char msg[8];
	for(size_t i = 0; i < 8; i++){
		msg[i] = frame.data[i];
	}

	unsigned int flag = 0;
	if(frame.id > 2047){
		flag = canMSG_EXT;
	}else{
		flag = canMSG_STD;
	}

	const canStatus ret = pfcanWrite(m_handle, frame.id, msg, frame.size, flag);
	if(ret != canOK){
		throw std::runtime_error("canWrite() failed with: " + get_error_text(ret));
	}
}


std::string CAN_Kvaser::get_error_text(canStatus status) const{
	char str[256];
	std::string result;

	const canStatus ret = pfcanGetErrorText(status, str, sizeof(str));
	if(ret != canOK){
		result = "Code " + std::to_string(status) + " (getting error text failed with Code " + std::to_string(ret) + ")";
	}else{
		result = str;
	}
	return result;
}



} // base
} // pilot

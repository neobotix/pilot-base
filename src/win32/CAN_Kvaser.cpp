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
#include <stdexcept>
#include <string>


namespace pilot {
namespace base {


template<typename T>
T* CAN_Kvaser::resolve(HINSTANCE dll, const char* name){
	auto ptr = GetProcAddress(dll, name);
	if(!ptr){
		throw std::runtime_error(std::string("Failed to resolve '") + name + "' from canlib32.dll");
	}
	return reinterpret_cast<T*>(ptr);
}


CAN_Kvaser::CAN_Kvaser(int channel, int baud_rate, const socketcan_options_t &socket_options){
	HINSTANCE dll = LoadLibrary("canlib32");

	if(dll == NULL){
		throw std::runtime_error("Dynamic library 'canlib32.dll' can't be loaded");
	}

	auto pfcanInitializeLibrary = resolve<fcanInitializeLibrary>(dll, "canInitializeLibrary");
	auto pfcanOpenChannel = resolve<fcanOpenChannel>(dll, "canOpenChannel");
	auto pfcanSetBusParams = resolve<fcanSetBusParams>(dll, "canSetBusParams");
	auto pfcanBusOn = resolve<fcanBusOn>(dll, "canBusOn");
	pfcanBusOff = resolve<fcanBusOff>(dll, "canBusOff");
	pfcanClose = resolve<fcanClose>(dll, "canClose");
	pfcanWrite = resolve<fcanWrite>(dll, "canWrite");
	pfcanReadWait = resolve<fcanReadWait>(dll, "canReadWait");
	pfcanGetErrorText = resolve<fcanGetErrorText>(dll, "canGetErrorText");
	pfcanReadErrorCounters = resolve<fcanReadErrorCounters>(dll, "canReadErrorCounters");
	pfcanIoCtl = resolve<fcanIoCtl>(dll, "canIoCtl");

	pfcanInitializeLibrary();

	m_handle = pfcanOpenChannel(channel, canOPEN_ACCEPT_VIRTUAL);
	if(m_handle < 0){
		throw std::runtime_error("canOpenChannel() failed with: " + get_error_text(static_cast<canStatus>(m_handle)));
	}

	long freq = 0;
	switch(baud_rate){
	case 1000000:
		freq = canBITRATE_1M;
		break;
	case 500000:
		freq = canBITRATE_500K;
		break;
	case 250000:
		freq = canBITRATE_250K;
		break;
	case 125000:
		freq = canBITRATE_125K;
		break;
	case 100000:
		freq = canBITRATE_100K;
		break;
	case 83000:
		freq = canBITRATE_83K;
		break;
	case 62000:
		freq = canBITRATE_62K;
		break;
	case 50000:
		freq = canBITRATE_50K;
		break;
	case 10000:
		freq = canBITRATE_10K;
		break;
	default:
		throw std::runtime_error("Baud rate not supported");
	}

	canStatus ret = pfcanSetBusParams(m_handle, freq, 0, 0, 0, 0, 0);
	if(ret != canOK){
		throw std::runtime_error("canSetBusParams() failed with: " + get_error_text(ret));
	}

	unsigned char error_reporting = socket_options.receive_error_frames ? 1 : 0;
	ret = pfcanIoCtl(m_handle, canIOCTL_SET_ERROR_FRAMES_REPORTING, &error_reporting, sizeof(error_reporting));
	if(ret != canOK){
		throw std::runtime_error("canIoCtl(canIOCTL_SET_ERROR_FRAMES_REPORTING) failed with: " + get_error_text(ret));
	}

	unsigned char local_txecho = socket_options.loopback ? 1 : 0;
	ret = pfcanIoCtl(m_handle, canIOCTL_SET_LOCAL_TXECHO, &local_txecho, sizeof(local_txecho));
	if(ret != canOK){
		throw std::runtime_error("canIoCtl(canIOCTL_SET_LOCAL_TXECHO) failed with: " + get_error_text(ret));
	}

	ret = pfcanBusOn(m_handle);
	if(ret != canOK){
		throw std::runtime_error("canBusOn() failed with: " + get_error_text(ret));
	}
}


CAN_Kvaser::~CAN_Kvaser(){
	close();
}


void CAN_Kvaser::close(){
	if(m_handle != canINVALID_HANDLE){
		pfcanBusOff(m_handle);
		pfcanClose(m_handle);
		m_handle = canINVALID_HANDLE;
	}
}

bool CAN_Kvaser::read(CAN_Frame &frame, int timeout_ms){
	long id = 0;
	unsigned char msg[8] = {};
	unsigned int dlc = 0;
	unsigned int flag = 0;
	unsigned long timestamp = 0;

	const canStatus ret = pfcanReadWait(m_handle, &id, msg, &dlc, &flag, &timestamp, static_cast<unsigned long>(timeout_ms));
	if(ret == canERR_NOMSG || ret == canERR_TIMEOUT){
		return false;
	}else if(ret != canOK){
		throw std::runtime_error("canReadWait() failed with: " + get_error_text(ret));
	}

	frame.time = vnx::get_time_micros();
	frame.id = id;
	frame.size = dlc;
	for(size_t i = 0; i < 8; i++){
		frame.data[i] = msg[i];
	}

	if(flag & canMSG_ERROR_FRAME){
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
	}

	return true;
}

void CAN_Kvaser::write(const CAN_Frame& frame){
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

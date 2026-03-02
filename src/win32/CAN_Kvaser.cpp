/*
 * CAN_Kvaser.cpp
 *
 *  Created on: Feb 26, 2026
 *      Author: jaw
 */

#include <pilot/base/CAN_Kvaser.h>
#include <pilot/base/socketcan_options_t.hxx>
#include <vnx/Time.h>

#include <canlib/canlib.h>


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


CAN_Kvaser::CAN_Kvaser(int channel, int bitrate, const socketcan_options_t &options) {
	const std::string libname = "canlib32";
	const auto dll = LoadLibrary(libname.c_str());
	if(!dll){
		throw std::runtime_error("Dynamic library " + libname + " can't be loaded");
	}
	p_canInitializeLibrary = get_proc<f_canInitializeLibrary>(dll, "canInitializeLibrary");
	p_canOpenChannel = get_proc<f_canOpenChannel>(dll, "canOpenChannel");
	p_canSetBusParams = get_proc<f_canSetBusParams>(dll, "canSetBusParams");
	p_canIoCtl = get_proc<f_canIoCtl>(dll, "canIoCtl");
	p_canBusOn = get_proc<f_canBusOn>(dll, "canBusOn");
	p_canBusOff = get_proc<f_canBusOff>(dll, "canBusOff");
	p_canClose = get_proc<f_canClose>(dll, "canClose");
	p_canReadWait = get_proc<f_canReadWait>(dll, "canReadWait");
	p_canWrite = get_proc<f_canWrite>(dll, "canWrite");
	p_canReadErrorCounters = get_proc<f_canReadErrorCounters>(dll, "canReadErrorCounters");
	p_canGetErrorText = get_proc<f_canGetErrorText>(dll, "canGetErrorText");

	p_canInitializeLibrary();
	handle = p_canOpenChannel(channel, canOPEN_ACCEPT_VIRTUAL);
	if(handle < 0){
		throw std::runtime_error("canOpenChannel() failed with: " + get_error_text(static_cast<canStatus>(handle)));
	}

	long freq;
	switch(bitrate){
		case 1000000: freq = canBITRATE_1M; break;
		case 500000: freq = canBITRATE_500K; break;
		case 250000: freq = canBITRATE_250K; break;
		case 125000: freq = canBITRATE_125K; break;
		case 100000: freq = canBITRATE_100K; break;
		case 62000: freq = canBITRATE_62K; break;
		case 50000: freq = canBITRATE_50K; break;
		case 83000: freq = canBITRATE_83K; break;
		case 10000: freq = canBITRATE_10K; break;
		default:
			throw std::logic_error("Bitrate not supported");
	}

	const auto result = p_canSetBusParams(handle, freq, 0, 0, 0, 0, 0);
	if(result != canOK){
		close();
		throw std::runtime_error("canSetBusParams() failed with: " + get_error_text(result));
	}

	// options.filter_list  ->  canSetAcceptanceFilter only supports bit masking
	// options.receive_own_messages  ->  not supported?
	unsigned char receive_error_frames = options.receive_error_frames;
	{
		const auto ret = p_canIoCtl(handle, canIOCTL_SET_ERROR_FRAMES_REPORTING, &receive_error_frames, sizeof(receive_error_frames));
		if(ret != canOK){
			close();
			throw std::runtime_error("canIoCtl(canIOCTL_SET_ERROR_FRAMES_REPORTING) failed with: " + get_error_text(ret));
		}
	}
	unsigned char loopback = options.loopback;
	{
		const auto ret = p_canIoCtl(handle, canIOCTL_SET_LOCAL_TXECHO, &loopback, sizeof(loopback));
		if(ret != canOK){
			close();
			throw std::runtime_error("canIoCtl(canIOCTL_SET_LOCAL_TXECHO) failed with: " + get_error_text(ret));
		}
	}

	const auto ret = p_canBusOn(handle);
	if(ret != canOK){
		close();
		throw std::runtime_error("canBusOn() failed with: " + get_error_text(ret));
	}
}


CAN_Kvaser::~CAN_Kvaser() {
	close();
}


void CAN_Kvaser::close() {
	p_canBusOff(handle);
	p_canClose(handle);
}


bool CAN_Kvaser::read(CAN_Frame &frame, int timeout_ms) {
	long id = 0;
	unsigned int size = 0;
	unsigned int flag = 0;

	const auto result = p_canReadWait(handle, &id, frame.data.data(), &size, &flag, NULL, timeout_ms);
	bool received = false;
	if(result == canOK){
		frame.time = vnx::get_time_micros();
		frame.id = id;
		frame.size = size;
		received = true;
	}else if(result != canERR_NOMSG){
		throw std::runtime_error("canReadWait() failed with: " + get_error_text(result));
	}
	if(flag & canMSG_ERROR_FRAME){
		can_error_t error;
		// error.error_classes  ->  no correspondence
		unsigned int rx_errors;
		unsigned int tx_errors;
		const auto ret = p_canReadErrorCounters(handle, &tx_errors, &rx_errors, NULL);
		if(ret == canOK){
			error.num_rx_errors = rx_errors;
			error.num_tx_errors = tx_errors;
		}
		frame.error = error;
	}
	return received;
}


void CAN_Kvaser::write(const CAN_Frame& frame) {
	long flags = 0;
	if(frame.id > 2047){
		flags |= canMSG_EXT;
	}

	auto copy = frame.data;
	const auto result = p_canWrite(handle, frame.id, copy.data(), frame.size, flags);
	if(result != canOK){
		throw std::runtime_error("canWrite() failed with: " + get_error_text(result));
	}
}


std::string CAN_Kvaser::get_error_text(canStatus status) const{
	char buffer[128];
	buffer[0] = '\0';
	const auto ret = p_canGetErrorText(status, buffer, sizeof(buffer));
	std::string result;
	if(ret == canOK){
		result = buffer;
	}else{
		result = "Code " + std::to_string(status) + " (getting error text failed with Code " + std::to_string(ret) + ")";
	}
	return result;
}


} // base
} // pilot

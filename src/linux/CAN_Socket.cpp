/*
 * CAN_Socket.cpp
 *
 *  Created on: Jun 10, 2020
 *      Author: mad
 */

#include <pilot/base/CAN_Socket.h>
#include <pilot/base/socketcan_options_t.hxx>

#include <vnx/vnx.h>

#include <string>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


namespace pilot {
namespace base {


const static std::map<decltype(CAN_ERR_TX_TIMEOUT), can_error_class_e> error_class_map = {
	{CAN_ERR_TX_TIMEOUT, can_error_class_e::TX_TIMEOUT},
	{CAN_ERR_LOSTARB, can_error_class_e::LOST_ARBITRATION},
	{CAN_ERR_CRTL, can_error_class_e::CONTROLLER},
	{CAN_ERR_PROT, can_error_class_e::PROTOCOL},
	{CAN_ERR_TRX, can_error_class_e::TRANSCEIVER},
	{CAN_ERR_ACK, can_error_class_e::NO_ACK},
	{CAN_ERR_BUSOFF, can_error_class_e::BUS_OFF},
	{CAN_ERR_BUSERROR, can_error_class_e::BUS_ERROR},
	{CAN_ERR_RESTARTED, can_error_class_e::RESTARTED},
};


CAN_Socket::CAN_Socket(const std::string& iface, const socketcan_options_t &socket_options)
{
	sock = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if(sock < 0) {
		throw std::runtime_error("socket() failed with: " + std::string(strerror(errno)));
	}

	ifreq ifr = {};
	::strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ - 1);
	if(::ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
		throw std::runtime_error("ioctl() failed with: " + std::string(strerror(errno)));
	}

	if(!socket_options.filter_list.empty()){
		std::vector<can_filter> filters;
		for(const auto &entry : socket_options.filter_list){
			can_filter filter;
			filter.can_id = entry;
			if(socket_options.is_block_list){
				filter.can_id |= CAN_INV_FILTER;
			}
			if(entry > CAN_SFF_MASK){
				filter.can_mask = CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK;
			}else{
				filter.can_mask = CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_SFF_MASK;
			}
			filters.push_back(filter);
		}
		if(setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, filters.data(), filters.size()*sizeof(can_filter)) < 0){
			throw std::runtime_error("setsockopt(CAN_RAW_FILTER) failed with: " + std::string(strerror(errno)));
		}
		if(socket_options.is_block_list){
			const int join_filters = 1;
			if(setsockopt(sock, SOL_CAN_RAW, CAN_RAW_JOIN_FILTERS, &join_filters, sizeof(join_filters)) < 0){
				throw std::runtime_error("setsockopt(CAN_RAW_JOIN_FILTERS) failed with: " + std::string(strerror(errno)));
			}
		}
	}
	{
		const can_err_mask_t error_mask = (socket_options.receive_error_frames ? CAN_ERR_MASK : 0);
		if(setsockopt(sock, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &error_mask, sizeof(error_mask)) < 0){
			throw std::runtime_error("setsockopt(CAN_RAW_ERR_FILTER) failed with: " + std::string(strerror(errno)));
		}
	}
	{
		const int loopback = socket_options.loopback;
		if(setsockopt(sock, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback)) < 0){
			throw std::runtime_error("setsockopt(CAN_RAW_LOOPBACK) failed with: " + std::string(strerror(errno)));
		}
	}
	{
		const int own = socket_options.receive_own_messages;
		if(setsockopt(sock, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &own, sizeof(own)) < 0){
			throw std::runtime_error("setsockopt(CAN_RAW_RECV_OWN_MSGS) failed with: " + std::string(strerror(errno)));
		}
	}

	sockaddr_can addr = {};
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if(::bind(sock, (sockaddr*)(&addr), sizeof(addr)) < 0) {
		throw std::runtime_error("bind() failed with: " + std::string(strerror(errno)));
	}
}

CAN_Socket::~CAN_Socket() {
	close();
}

void CAN_Socket::close()
{
	if(sock >= 0) {
		::close(sock);
		sock = -1;
	}
}

bool CAN_Socket::read(CAN_Frame &frame, int timeout_ms)
{
	if(timeout_ms >= 0){
		::fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(sock, &read_set);

		struct timeval timeout = {int32_t(timeout_ms / 1000), int32_t((timeout_ms % 1000) * 1000)};
		if(::select(sock + 1, &read_set, 0, 0, &timeout) < 1) {
			return false;
		}
	}

	::can_frame data = {};
	const auto res = ::read(sock, &data, sizeof(data));
	if(res != sizeof(data)) {
		throw std::runtime_error("read() failed with: " + std::string(strerror(errno)));
	}

	frame.time = vnx::get_time_micros();
	frame.id = data.can_id & CAN_EFF_MASK;
	frame.size = data.can_dlc;
	for(int i = 0; i < 8; ++i) {
		frame.data[i] = data.data[i];
	}

	if(data.can_id & CAN_ERR_FLAG){
		can_error_t error;
		for(const auto &entry : error_class_map){
			if(data.can_id & entry.first){
				error.error_classes.insert(entry.second);
			}
		}
		error.num_tx_errors = frame.data[6];
		error.num_rx_errors = frame.data[7];
		frame.error = error;
	}

	return true;
}

void CAN_Socket::write(const CAN_Frame& frame)
{
	::can_frame out = {};
	out.can_id = frame.id;
	if(frame.id > CAN_SFF_MASK){
		out.can_id |= CAN_EFF_FLAG;
	}
	out.can_dlc = frame.size;
	for(int i = 0; i < 8; ++i) {
		out.data[i] = frame.data[i];
	}

	const auto res = ::write(sock, &out, sizeof(out));
	if(res != sizeof(out)) {
		throw std::runtime_error("write() failed with: " + std::string(strerror(errno)));
	}
}


} // base
} // pilot

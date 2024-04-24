/*
 * UDP_Socket.cpp
 *
 *  Created on: Apr 23, 2024
 *      Author: jaw
 */

#include <pilot/base/UDP_Socket.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#endif


namespace pilot {
namespace base {


UDP_Socket::UDP_Socket(const std::string& _vnx_name)
	:	UDP_SocketBase(_vnx_name),
		packets_received(0),
		bytes_received(0),
		msg_sent(0),
		packets_sent(0),
		bytes_sent(0)
{
	socket = static_cast<socket_t>(INVALID_SOCKET);
}


void UDP_Socket::main(){
	subscribe(input, 100);

	set_timer_millis(init_interval_ms, std::bind(&UDP_Socket::initialize, this));
	if(stats_interval_ms > 0){
		set_timer_millis(stats_interval_ms, std::bind(&UDP_Socket::print_stats, this));
	}

	Super::main();

	cleanup();
	if(read_thread.joinable()){
		read_thread.join();
	}
}


void UDP_Socket::handle(std::shared_ptr<const DataPacket> value){
	if(!is_initialized){
		return;
	}

	size_t sent = 0;
	while(sent < value->payload.size()){
		const auto buf = value->payload.data() + sent;
		const size_t len = value->payload.size() - sent;
#ifdef _WIN32
		const auto result = send(socket, reinterpret_cast<const char*>(buf), len, 0);
#else
		const auto result = send(socket, buf, len, MSG_NOSIGNAL);
#endif
		if(result < 0){
			throw std::runtime_error("send() failed with: " + std::string(strerror(errno)));
		}
		sent += result;
		bytes_sent += result;
		packets_sent++;
	}
	msg_sent++;
}


void UDP_Socket::initialize(){
	if(is_initialized){
		return;
	}


	socket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if(socket == INVALID_SOCKET) {
#ifdef _WIN32
		throw std::runtime_error("socket() failed with: " + std::to_string(WSAGetLastError()));
#else
		throw std::runtime_error("socket() failed with: " + std::string(std::strerror(errno)));
#endif
	}


	if(port != 0){
		::sockaddr_in myaddr = {};
		myaddr.sin_family = AF_INET;
		myaddr.sin_port = htons(port);
		myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		if(::bind(socket, (::sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
			cleanup();
#ifdef _WIN32
			throw std::runtime_error("bind() failed with: " + std::to_string(WSAGetLastError()));
#else
			throw std::runtime_error("bind() failed with: " + std::string(std::strerror(errno)));
#endif
		}
	}


	if(address){
		addrinfo hints = {};
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_DGRAM;

		addrinfo *info;
		{
			const std::string port_str = std::to_string(address->port);
			const auto result = getaddrinfo(address->address.c_str(), port_str.c_str(), &hints, &info);
			if(result < 0){
				cleanup();
				throw std::runtime_error("getaddrinfo() failed with: " + std::string(gai_strerror(result)));
			}
		}

		bool success = false;
		std::string errors;
		for(addrinfo *r=info; r!=NULL; r=r->ai_next){
			const auto result = ::connect(socket, r->ai_addr, r->ai_addrlen);
			if(result == 0){
				success = true;
				break;
			}else{
				if(!errors.empty()){
					errors += ", ";
				}
				errors += std::string(strerror(errno));
			}
		}
		freeaddrinfo(info);

		if(!success){
			cleanup();
			throw std::runtime_error("connect() failed with: " + errors);
		}
	}


	is_initialized = true;
	read_thread = std::thread(std::bind(&UDP_Socket::read_loop, this));
}


void UDP_Socket::cleanup(){
	is_initialized = false;
	if(socket != INVALID_SOCKET){
#ifdef _WIN32
		closesocket(socket);
#else
		::close(socket);
#endif
	}
	socket = INVALID_SOCKET;
}


ssize_t UDP_Socket::receive(socket_t socket, void* buf, size_t len, int timeout_ms) const{
	if(timeout_ms >= 0){
		::fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(socket, &read_set);

		timeval tv;
		tv.tv_sec = timeout_ms / 1000;
		tv.tv_usec = (timeout_ms % 1000) * 1000;
		if(::select(socket+1, &read_set, NULL, NULL, &tv) < 1) {
			return 0;
		}
	}

#ifdef _WIN32
	const auto num_bytes = recv(socket, (char*)buf, len, 0);
	if(num_bytes < 0){
		throw std::runtime_error("recv() failed with: " + std::to_string(WSAGetLastError()));
	}
#else
	const auto num_bytes = ::recvfrom(socket, buf, len, 0, 0, 0);
	if(num_bytes < 0) {
		throw std::runtime_error("recvfrom() failed with: " + std::string(strerror(errno)));
	}
#endif
	return num_bytes;
}


void UDP_Socket::print_stats(){
	const auto packets_received_ = packets_received.exchange(0);
	const auto bytes_received_ = bytes_received.exchange(0);
	const auto msg_sent_ = msg_sent.exchange(0);
	const auto packets_sent_ = packets_sent.exchange(0);
	const auto bytes_sent_ = bytes_sent.exchange(0);
	log(INFO)
		<< (1000 * msg_sent_) / stats_interval_ms << " msg/s"
		<< ", "
		<< (1000 * packets_sent_) / stats_interval_ms << " pkt/s"
		<< ", "
		<< ((1000 * bytes_sent_) / 1024) / stats_interval_ms << " KiB/s"
		<< " sent"
		<< ", "
		<< (1000 * packets_received_) / stats_interval_ms << " pkt/s"
		<< ", "
		<< ((1000 * bytes_received_) / 1024) / stats_interval_ms << " KiB/s"
		<< " received"
	;
}


void UDP_Socket::read_loop(){
	while(vnx_do_run()){
		try {
			auto sample = DataPacket::create();
			sample->time = vnx::get_time_micros();
			sample->payload.resize(max_packet_size);

			const auto num_bytes = receive(socket, sample->payload.data(), sample->payload.size(), read_timeout_ms);
			if(num_bytes > 0) {
				sample->payload.resize(num_bytes);
				publish(sample, output);
				bytes_received += num_bytes;
				packets_received++;
			}
		}catch(const std::exception& ex) {
			if(vnx_do_run()) {
				//log(WARN) << ex.what();
				std::this_thread::sleep_for(std::chrono::milliseconds(error_interval_ms));
			}
		}
	}
}


} // base
} // pilot

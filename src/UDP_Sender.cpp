#include <pilot/base/UDP_Sender.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#endif
#include <unistd.h>


namespace pilot{
namespace base{


UDP_Sender::UDP_Sender(const std::string &vnx_name_):
	UDP_SenderBase(vnx_name_)
{
	socket = static_cast<socket_t>(INVALID_SOCKET);
}


void UDP_Sender::main(){
	subscribe(input);
	if(stats_interval_ms > 0){
		set_timer_millis(stats_interval_ms, std::bind(&UDP_Sender::print_stats, this));
	}

	setup();

	Super::main();

	cleanup();
}


void UDP_Sender::handle(std::shared_ptr<const DataPacket> value){
	size_t sent = 0;
	while(sent < value->payload.size()){
		const auto buf = value->payload.data() + sent;
		const size_t len = value->payload.size() - sent;
#ifdef _WIN32
		const auto result = send(socket, reinterpret_cast<const char*>(buf), size, 0);
#else
		const auto result = send(socket, buf, len, MSG_NOSIGNAL);
#endif
		if(result < 0){
			throw std::runtime_error("send() failed with: " + std::string(strerror(errno)));
		}
		sent += result;
		bytes_sent += result;
	}
	packet_counter++;
}


void UDP_Sender::setup(){
	socket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if(socket == INVALID_SOCKET){
		throw std::runtime_error("socket() failed with: " + std::string(strerror(errno)));
	}

	addrinfo hints = {};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	addrinfo *info;
	{
		const std::string port_str = std::to_string(port);
		const auto result = getaddrinfo(address.c_str(), port_str.c_str(), &hints, &info);
		if(result < 0){
			throw std::runtime_error("getaddrinfo() failed with: " + std::string(gai_strerror(result)));
		}
	}

	bool success = false;
	std::string errors;
	for(addrinfo *r=info; r!=NULL; r=r->ai_next){
		const auto result = connect(socket, r->ai_addr, r->ai_addrlen);
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
		throw std::runtime_error("connect() failed with: " + errors);
	}
}


void UDP_Sender::cleanup(){
#ifdef _WIN32
	closesocket(socket);
#else
	::close(socket);
#endif
}


void UDP_Sender::print_stats(){
	log(INFO) << (1000 * packet_counter) / stats_interval_ms << " packets/s, "
			<< ((1000 * bytes_sent) / 1024) / stats_interval_ms << " KiB/s sent";
	bytes_sent = 0;
	packet_counter = 0;
}


} // base
} // pilot

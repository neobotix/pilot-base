/*
 * UDP_Receiver.cpp
 *
 *  Created on: Jun 3, 2020
 *      Author: mad
 */

#include <pilot/base/UDP_Receiver.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>


namespace pilot {
namespace base {

void UDP_Receiver::open_port()
{
	close_port();

	m_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
	if(m_fd < 0) {
		throw std::runtime_error("socket() failed with: " + std::string(std::strerror(errno)));
	}

	::sockaddr_in myaddr;
	memset((char*)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port);
	if(::bind(m_fd, (::sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
		throw std::runtime_error("bind() failed with: " + std::string(std::strerror(errno)));
	}
}

void UDP_Receiver::close_port()
{
	if(m_fd >= 0) {
		::close(m_fd);
		m_fd = -1;
	}
}


} // base
} // pilot

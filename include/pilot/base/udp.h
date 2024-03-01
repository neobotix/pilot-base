/*
 * udp.h
 *
 *  Created on: Mar 1, 2024
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_UDP_H_
#define INCLUDE_PILOT_BASE_UDP_H_

#include <sys/types.h>


namespace pilot {
namespace base {


ssize_t udp_recv_packet(int socket, void* buf, size_t len, int timeout_ms);


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_UDP_H_ */

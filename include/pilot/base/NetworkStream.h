/*
 * NetworkStream.h
 *
 *  Created on: Jan 25, 2021
 *      Author: jaw
 */

#ifndef INCLUDE_PILOT_BASE_NETWORKSTREAM_H_
#define INCLUDE_PILOT_BASE_NETWORKSTREAM_H_

#include <pilot/base/NetworkStreamBase.hxx>
#include <vnx/Endpoint.hxx>
#include <vnx/InputStream.h>
#include <vnx/OutputStream.h>


namespace pilot {
namespace base {

class NetworkStream : public NetworkStreamBase {
public:
	NetworkStream(const std::string& _vnx_name);
	
protected:
	void init() override;
	void main() override;
	
	bool is_connected() const override;
	void connect() override;
	void disconnect() override;

	void handle(std::shared_ptr<const DataPacket> value) override;
	bool vnx_shutdown() override;
	
private:
	std::shared_ptr<const vnx::Endpoint> endpoint;
	int socket = -1;
	vnx::SocketInputStream input_stream;
	vnx::SocketOutputStream output_stream;
	bool connected = false;

	int64_t num_read = 0;
	int64_t num_write = 0;
	int64_t num_write_fail = 0;
	
	size_t read(unsigned char *buf, size_t len);
	void write(const unsigned char *buf, size_t len);
	void read_loop(const vnx::Hash64 &module_addr);
	void error_wait() const;
	void print_stats();
};


} // base
} // pilot

#endif /* INCLUDE_PILOT_BASE_NETWORKSTREAM_H_ */

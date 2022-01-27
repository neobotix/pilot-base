/*
 * NetworkStream.cpp
 *
 *  Created on: Jan 25, 2021
 *      Author: jaw
 */

#include <pilot/base/NetworkStream.h>
#include <pilot/base/NetworkStreamClient.hxx>

#include <unistd.h>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif


namespace pilot {
namespace base {


NetworkStream::NetworkStream(const std::string& _vnx_name)
	:	NetworkStreamBase(_vnx_name)
{
}


void NetworkStream::init(){
	subscribe(input, 10);
	endpoint = vnx::Endpoint::from_url(address);
}


void NetworkStream::main(){
	if(stats_interval_ms > 0){
		set_timer_millis(stats_interval_ms, std::bind(&NetworkStream::print_stats, this));
	}

	try {
		connect();
	}
	catch(const std::exception& ex) {
		log(WARN) << ex.what();
	}

	// start read loop
	std::thread read_thread;
	{
		// open a private pipe for read_loop()
		const auto module_addr = vnx::Hash64::rand();
		vnx::open_pipe(module_addr, this, UNLIMITED);
		// start read thread
		read_thread = std::thread(&NetworkStream::read_loop, this, module_addr);
	}

	Super::main();

	// force read_loop to exit
	if(socket >= 0) {
#ifdef _WIN32
		::shutdown(socket, SD_BOTH);
#else
		::shutdown(socket, SHUT_RDWR);
#endif
	}

	disconnect();
	read_thread.join();
}


void NetworkStream::connect(){
	if(socket == -1){
		socket = endpoint->open();
		input_stream.reset(socket);
		output_stream.reset(socket);
	}
	endpoint->connect(socket);
	is_connected = true;
}


void NetworkStream::disconnect(){
	if(socket >= 0) {
#ifdef _WIN32
		::closesocket(socket);
#else
		::close(socket);
#endif
		socket = -1;
		input_stream.reset(socket);
		output_stream.reset(socket);
		is_connected = false;
	}
}


size_t NetworkStream::read(unsigned char *buf, size_t len){
	size_t result = input_stream.read(buf, len);
	if(result == 0){
		throw std::underflow_error("EOF");
	}
	return result;
}


void NetworkStream::write(const unsigned char *buf, size_t len){
	output_stream.write(buf, len);
}


void NetworkStream::handle(std::shared_ptr<const DataPacket> value){
	if(is_connected){
		num_write_fail++;
		write(value->payload.data(), value->payload.size());
		num_write_fail--;
		num_write++;
	}
}


void NetworkStream::print_stats(){
	log(INFO) <<
		(1000 * num_read) / stats_interval_ms << " msgs/s receive, "
		<< (1000 * num_write) / stats_interval_ms << " msgs/s send, "
		<< num_write_fail << " failed";
	num_read = 0;
	num_write = 0;
}


void NetworkStream::read_loop(const vnx::Hash64 &module_addr){
	NetworkStreamClient client(module_addr);

	while(vnx_do_run()){
		while(vnx_do_run() && is_connected){
			auto data = DataPacket::create();
			data->payload.resize(read_buffer_size);
			try{
				size_t bytes_read = read(data->payload.data(), data->payload.size());
				data->payload.resize(bytes_read);
				data->time = vnx::get_time_micros();
				publish(data, output);
				num_read++;
			}catch(const std::exception& ex){
				log(WARN) << ex.what();
				break;
			}
		}

		bool closed = false;
		while(vnx_do_run()){
			try{
				if(!closed){
					client.disconnect();
					closed = true;
				}
				client.connect();
				break;
			}catch(const std::exception &err){
				log(WARN) << err.what();
				error_wait();
			}
		}
	}
}


void NetworkStream::error_wait() const{
	int wait_ms = error_interval_ms;
	while(wait_ms > 0 && vnx_do_run()){
		int micro_wait_ms = 10;
		if(micro_wait_ms > wait_ms){
			micro_wait_ms = wait_ms;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(micro_wait_ms));
		wait_ms -= micro_wait_ms;
	}
}


} // base
} // pilot

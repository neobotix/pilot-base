
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_UDP_ReceiverBase_HXX_
#define INCLUDE_pilot_base_UDP_ReceiverBase_HXX_

#include <pilot/base/package.hxx>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace pilot {
namespace base {

class UDP_ReceiverBase : public ::vnx::Module {
public:
	
	::vnx::TopicPtr output;
	int32_t port = 0;
	int32_t max_packet_size = 65536;
	int32_t read_timeout_ms = 200;
	int32_t error_interval_ms = 1000;
	int32_t stats_interval_ms = 10000;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x5c0111dff18f907bull;
	
	UDP_ReceiverBase(const std::string& _vnx_name);
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const UDP_ReceiverBase& _value);
	friend std::istream& operator>>(std::istream& _in, UDP_ReceiverBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	using Super::handle;
	
	virtual void open_port() = 0;
	virtual void close_port() = 0;
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};


} // namespace pilot
} // namespace base


namespace vnx {

} // vnx

#endif // INCLUDE_pilot_base_UDP_ReceiverBase_HXX_

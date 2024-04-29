
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_UDP_SocketBase_HXX_
#define INCLUDE_pilot_base_UDP_SocketBase_HXX_

#include <pilot/base/package.hxx>
#include <pilot/base/DataPacket.hxx>
#include <pilot/base/in_address_t.hxx>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace pilot {
namespace base {

class UDP_SocketBase : public ::vnx::Module {
public:
	
	::vnx::TopicPtr input;
	::vnx::TopicPtr output;
	int32_t port = 0;
	vnx::optional<::pilot::base::in_address_t> address;
	int32_t max_packet_size = 65536;
	int32_t read_timeout_ms = 200;
	int32_t init_interval_ms = 1000;
	int32_t error_interval_ms = 1000;
	int32_t stats_interval_ms = 10000;
	int32_t shutdown_delay_ms = 200;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xed63df42c27a66ebull;
	
	UDP_SocketBase(const std::string& _vnx_name);
	
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
	
	friend std::ostream& operator<<(std::ostream& _out, const UDP_SocketBase& _value);
	friend std::istream& operator>>(std::istream& _in, UDP_SocketBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	using Super::handle;
	
	virtual void handle(std::shared_ptr<const ::pilot::base::DataPacket> _value) {}
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};


} // namespace pilot
} // namespace base


namespace vnx {

} // vnx

#endif // INCLUDE_pilot_base_UDP_SocketBase_HXX_

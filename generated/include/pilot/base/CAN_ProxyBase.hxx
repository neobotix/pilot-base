
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_CAN_ProxyBase_HXX_
#define INCLUDE_pilot_base_CAN_ProxyBase_HXX_

#include <pilot/base/package.hxx>
#include <pilot/base/CAN_Frame.hxx>
#include <pilot/base/can_adapter_e.hxx>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace pilot {
namespace base {

class CAN_ProxyBase : public ::vnx::Module {
public:
	
	::vnx::TopicPtr input;
	::vnx::TopicPtr output;
	::pilot::base::can_adapter_e adapter = ::pilot::base::can_adapter_e::SOCKETCAN;
	std::string device;
	int32_t baud_rate = 0;
	vnx::bool_t is_big_endian = 0;
	int32_t read_timeout_ms = 200;
	int32_t stats_interval_ms = 10000;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	CAN_ProxyBase(const std::string& _vnx_name);
	
	vnx::Hash64 get_type_hash() const override;
	const char* get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const CAN_ProxyBase& _value);
	friend std::istream& operator>>(std::istream& _in, CAN_ProxyBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	virtual void handle(std::shared_ptr<const ::pilot::base::CAN_Frame> _value) {}
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Sample> _sample) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};


} // namespace pilot
} // namespace base

#endif // INCLUDE_pilot_base_CAN_ProxyBase_HXX_

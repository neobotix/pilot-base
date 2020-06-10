
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_pilot_base_JoystickBase_HXX_
#define INCLUDE_pilot_base_JoystickBase_HXX_

#include <pilot/base/package.hxx>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace pilot {
namespace base {

class JoystickBase : public ::vnx::Module {
public:
	
	::vnx::TopicPtr output;
	std::string device;
	vnx::bool_t invert = false;
	int32_t read_timeout_ms = 200;
	int32_t error_interval_ms = 1000;
	int32_t stats_interval_ms = 10000;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	JoystickBase(const std::string& _vnx_name);
	
	vnx::Hash64 get_type_hash() const;
	const char* get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	friend std::ostream& operator<<(std::ostream& _out, const JoystickBase& _value);
	friend std::istream& operator>>(std::istream& _in, JoystickBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	virtual void close_device() = 0;
	virtual void open_device() = 0;
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Sample> _sample) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};


} // namespace pilot
} // namespace base

#endif // INCLUDE_pilot_base_JoystickBase_HXX_

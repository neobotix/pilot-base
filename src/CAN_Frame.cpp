/*
 * CAN_Frame.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: mad
 */

#include <pilot/base/CAN_Frame.hxx>


namespace pilot {
namespace base {

static int from_dbc(int bit, int size) {
	bit = bit - 2 * (bit % 8) + 7;
	bit = bit + size - 1;
	bit = bit - 2 * (bit % 8) + 7;
	return bit;
}

vnx::bool_t CAN_Frame::get_bit(const ::int32_t& pos) const {
	return data[pos / 8] & (1 << (pos % 8));
}

void CAN_Frame::set_bit(const ::int32_t& pos, const vnx::bool_t& value) {
	if(value) {
		data[pos / 8] |= (1 << (pos % 8));
	} else {
		data[pos / 8] &= ~(1 << (pos % 8));
	}
}

vnx::bool_t CAN_Frame::get_bool(const ::int32_t& pos) const {
	return get_bit(pos);
}

::int32_t CAN_Frame::get_int(const ::int32_t& pos, const ::int32_t& size, const ::int32_t& offset) const {
	if(size > 32) {
		throw std::logic_error("size > 32");
	}
	const uint32_t max = uint32_t(1) << (size - 1);
	const uint32_t value = get_uint(pos, size, 0);
	int32_t out;
	if(value >= max) {
		out = -1 * (max - (value - max));		// convert to negative value
	} else {
		out = value;
	}
	return out + offset;
}

::uint32_t CAN_Frame::get_uint(const ::int32_t& pos, const ::int32_t& size, const ::int32_t& offset) const {
	uint32_t value = 0;
	if(is_big_endian) {
		int bit = pos;
		for(int i = 0; i < size; ++i) {
			value |= uint32_t(get_bit(bit++)) << i;
			if(bit % 8 == 0) {
				bit -= 16;
			}
		}
	} else {
		for(int i = 0; i < size; ++i) {
			value |= uint32_t(get_bit(pos + i)) << i;
		}
	}
	return value + offset;
}

vnx::float32_t CAN_Frame::get_float_signed(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& scale, const vnx::float32_t& offset) const {
	const int32_t value = get_int(pos, size, 0);
	return value * scale + offset;
}

vnx::float32_t CAN_Frame::get_float_unsigned(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& scale, const vnx::float32_t& offset) const {
	const uint32_t value = get_uint(pos, size, 0);
	return value * scale + offset;
}

void CAN_Frame::set_bool(const ::int32_t& pos, const vnx::bool_t& value) {
	set_bit(pos, value);
}

void CAN_Frame::set_int(const ::int32_t& pos, const ::int32_t& size, const ::int32_t& value_, const ::int32_t& offset) {
	if(size > 32) {
		throw std::logic_error("size > 32");
	}
	const uint32_t max = uint32_t(1) << (size - 1);
	int32_t value = value_ - offset;
	if(value >= int32_t(max)) {
		value = max - 1;
	} else if(value < -1 * int32_t(max)) {
		value = -max;
	}
	uint32_t out;
	if(value < 0) {
		out = uint32_t(value + max) + max;		// convert to positive value
	} else {
		out = value;
	}
	set_uint(pos, size, out, 0);
}

void CAN_Frame::set_uint(const ::int32_t& pos, const ::int32_t& size, const ::uint32_t& value_, const ::int32_t& offset) {
	if(size > 32) {
		throw std::logic_error("size > 32");
	}
	const uint32_t max = (uint64_t(1) << size) - 1;
	int32_t value = value_ - offset;
	if(value > max) {
		value = max;
	}
	if(is_big_endian) {
		int bit = pos;
		for(int i = 0; i < size; ++i) {
			set_bit(bit++, value & (1 << i));
			if(bit % 8 == 0) {
				bit -= 16;
			}
		}
	} else {
		for(int i = 0; i < size; ++i) {
			set_bit(pos + i, value & (1 << i));
		}
	}
}

void CAN_Frame::set_float_signed(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& value, const vnx::float32_t& scale, const vnx::float32_t& offset) {
	set_int(pos, size, (value - offset) / scale, 0);
}

void CAN_Frame::set_float_unsigned(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& value, const vnx::float32_t& scale, const vnx::float32_t& offset) {
	set_uint(pos, size, (value - offset) / scale, 0);
}

vnx::bool_t CAN_Frame::get_bool_dbc(const ::int32_t& pos) const {
	return get_bool(is_big_endian ? from_dbc(pos, 1) : pos);
}

::int32_t CAN_Frame::get_int_dbc(const ::int32_t& pos, const ::int32_t& size, const ::int32_t& offset) const {
	return get_int(is_big_endian ? from_dbc(pos, size) : pos, size, offset);
}

::uint32_t CAN_Frame::get_uint_dbc(const ::int32_t& pos, const ::int32_t& size, const ::int32_t& offset) const {
	return get_uint(is_big_endian ? from_dbc(pos, size) : pos, size, offset);
}

vnx::float32_t CAN_Frame::get_float_signed_dbc(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& scale, const vnx::float32_t& offset) const {
	return get_float_signed(is_big_endian ? from_dbc(pos, size) : pos, size, scale, offset);
}

vnx::float32_t CAN_Frame::get_float_unsigned_dbc(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& scale, const vnx::float32_t& offset) const {
	return get_float_unsigned(is_big_endian ? from_dbc(pos, size) : pos, size, scale, offset);
}

void CAN_Frame::set_bool_dbc(const ::int32_t& pos, const vnx::bool_t& value) {
	set_bool(is_big_endian ? from_dbc(pos, 1) : pos, value);
}

void CAN_Frame::set_int_dbc(const ::int32_t& pos, const ::int32_t& size, const ::int32_t& value, const ::int32_t& offset) {
	set_int(is_big_endian ? from_dbc(pos, size) : pos, size, value, offset);
}

void CAN_Frame::set_uint_dbc(const ::int32_t& pos, const ::int32_t& size, const ::uint32_t& value, const ::int32_t& offset) {
	set_uint(is_big_endian ? from_dbc(pos, size) : pos, size, value, offset);
}

void CAN_Frame::set_float_signed_dbc(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& value, const vnx::float32_t& scale, const vnx::float32_t& offset) {
	set_float_signed(is_big_endian ? from_dbc(pos, size) : pos, size, value, scale, offset);
}

void CAN_Frame::set_float_unsigned_dbc(const ::int32_t& pos, const ::int32_t& size, const vnx::float32_t& value, const vnx::float32_t& scale, const vnx::float32_t& offset) {
	set_float_unsigned(is_big_endian ? from_dbc(pos, size) : pos, size, value, scale, offset);
}


} // base
} // pilot


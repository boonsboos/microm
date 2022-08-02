#include "mvalue.hpp"

MValue::MValue()
{
	v.u8 = 0;
	t = U8;
}

MValue::MValue(uint8_t a)
{
	std::cout << "New byte!\n";
	v.u8 = a;
	t = U8;
}

MValue::MValue(uint16_t a)
{
	v.u16 = a;
	t = U16;
}

MValue::MValue(uint32_t a)
{
	v.u32 = a;
	t = U32;
}

MValue::MValue(uint64_t a)
{
	v.u64 = a;
	t = U64;
}

MValue::MValue(int8_t a)
{
	v.i8 = a;
	t = I8;
}

MValue::MValue(int16_t a)
{
	v.i16 = a;
	t = I16;
}

MValue::MValue(int32_t a)
{
	v.i32 = a;
	t = I32;
}
MValue::MValue(int64_t a)
{
	v.i64 = a;
	t = I64;
}

MValue::MValue(float a)
{
	v.f32 = a;
	t = F32;
}

MValue::MValue(double a)
{
	v.f64 = a;
	t = F64;
}

MValue::MValue(uint8_t a, size_t len)
{
	this->t = U8;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(uint16_t a, size_t len)
{
	this->t = U16;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(uint32_t a, size_t len)
{
	this->t = U32;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(uint64_t a, size_t len)
{
	this->t = U64;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(int8_t a, size_t len)
{
	this->t = I8;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(int16_t a, size_t len)
{
	this->t = I16;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(int32_t a, size_t len)
{
	this->t = I32;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(int64_t a, size_t len)
{
	this->t = I64;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(float a, size_t len)
{
	this->t = F32;
	this->is_list = true;
	this->len = len;
}

MValue::MValue(double a, size_t len)
{
	this->t = F64;
	this->is_list = true;
	this->len = len;
}

std::string MValue::to_string() {
	switch (t) {
		case U8 : return std::to_string(v.u8);
		case U16: return std::to_string(v.u16);
		case U32: return std::to_string(v.u32);
		case U64: return std::to_string(v.u64); 
		case I8 : return std::to_string(v.i8);
		case I16: return std::to_string(v.i16);
		case I32: return std::to_string(v.i32);
		case I64: return std::to_string(v.i64);
		case F32: return std::to_string(v.f32);
		case F64: return std::to_string(v.f64);
		default: return "";
	}
}
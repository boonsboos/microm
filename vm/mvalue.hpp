#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "mexcept.hpp"

using std::vector;

union Value
{
	uint8_t  u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
	int8_t   i8;
	int16_t  i16;
	int32_t  i32;
	int64_t  i64;
	float    f32;
	double   f64;
};

enum Type
{
	U8,
	U16,
	U32,
	U64,
	I8,
	I16,
	I32,
	I64,
	F32,
	F64
};

inline std::string type_to_string(Type t)
{
	switch(t) {
		case U8:  return "U8";
		case U16: return "U16";
		case U32: return "U32";
		case U64: return "U64";
		case I8:  return "I8";
		case I16: return "I16";
		case I32: return "I32";
		case I64: return "I64";
		case F32: return "F32";
		case F64: return "F64";
		default: return "UNREACHABLE";
	}
}

class MValue
{	
public:
	Value  v;
	Type   t;
	
	// list stuff
	bool   is_list   = false;
	size_t len;
	Value* l = new Value[1];
	
	~MValue() { /*delete[] l;*/ }

	MValue(); // makes U8 with value 0
	MValue(const MValue &a) {this->v=a.v;this->t=a.t;this->is_list=a.is_list;this->len=a.len;this->l=a.l;}
	MValue(uint8_t  a);
	MValue(uint16_t a);
	MValue(uint32_t a);
	MValue(uint64_t a);
	MValue(int8_t   a);
	MValue(int16_t  a);
	MValue(int32_t  a);
	MValue(int64_t  a);
	MValue(float    a);
	MValue(double   a);
	MValue(uint8_t  a, size_t len);
	MValue(uint16_t a, size_t len);
	MValue(uint32_t a, size_t len);
	MValue(uint64_t a, size_t len);
	MValue(int8_t   a, size_t len);
	MValue(int16_t  a, size_t len);
	MValue(int32_t  a, size_t len);
	MValue(int64_t  a, size_t len);
	MValue(float    a, size_t len);
	MValue(double   a, size_t len);

	std::string to_string();

	inline std::ostream& operator<< (std::ostream &out) {
		return out << this->to_string();
	}

	// ugly operator bazinga
	inline MValue operator+ (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("ADD: cannot add with lists\n");

		if (this->t != a.t)
			throw TYPE_ERROR("ADD", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8 + a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16+a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32+a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64+a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8 + a.v.i8));
			case I16: return MValue(int16_t (this->v.i16+a.v.i16));
			case I32: return MValue(int32_t (this->v.i32+a.v.i32));
			case I64: return MValue(int64_t (this->v.i64+a.v.i64));
			case F32: return MValue(float   (this->v.f32+a.v.f32));
			case F64: return MValue(double  (this->v.f64+a.v.f64));
			default:  return MValue(uint8_t (this->v.u8 + a.v.u8)); // unreachable, but just in case
		}
	}

	inline MValue operator- () {
		if (this->is_list)
			throw MExcept("NEG: cannot negate a list\n");

		if (this->t < I8)
			throw MExcept("NEG: cannot negate unsigned numbers\n");

		switch(this->t) {
			case I8 : return MValue(int8_t  (-(this->v.i8)));
			case I16: return MValue(int16_t (-(this->v.i16)));
			case I32: return MValue(int32_t (-(this->v.i32)));
			case I64: return MValue(int64_t (-(this->v.i64)));
			case F32: return MValue(float   (-(this->v.f32)));
			case F64: return MValue(double  (-(this->v.f64)));
			default:  return MValue(int8_t  (-(this->v.i8))); // unreachable, but just in case
		}
	}

	inline MValue operator- (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("SUB: cannot subtract lists\n");

		if (this->t != a.t)
			throw TYPE_ERROR("SUB", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8 - a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16-a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32-a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64-a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8 - a.v.i8));
			case I16: return MValue(int16_t (this->v.i16-a.v.i16));
			case I32: return MValue(int32_t (this->v.i32-a.v.i32));
			case I64: return MValue(int64_t (this->v.i64-a.v.i64));
			case F32: return MValue(float   (this->v.f32-a.v.f32));
			case F64: return MValue(double  (this->v.f64-a.v.f64));
			default:  return MValue(uint8_t (this->v.u8 - a.v.u8)); // unreachable, but just in case
		}
	}

	inline MValue operator* (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("MUL: cannot multiply lists\n");

		if (this->t != a.t)
			throw TYPE_ERROR("MUL", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8 * a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16*a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32*a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64*a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8 * a.v.i8));
			case I16: return MValue(int16_t (this->v.i16*a.v.i16));
			case I32: return MValue(int32_t (this->v.i32*a.v.i32));
			case I64: return MValue(int64_t (this->v.i64*a.v.i64));
			case F32: return MValue(float   (this->v.f32*a.v.f32));
			case F64: return MValue(double  (this->v.f64*a.v.f64));
			default:  return MValue(uint8_t (this->v.u8 * a.v.u8)); // unreachable, but just in case
		}
	}

	inline MValue operator/ (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("DIV: cannot divide lists\n");

		if (this->t != a.t)
			throw TYPE_ERROR("DIV", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8 / a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16/a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32/a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64/a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8 / a.v.i8));
			case I16: return MValue(int16_t (this->v.i16/a.v.i16));
			case I32: return MValue(int32_t (this->v.i32/a.v.i32));
			case I64: return MValue(int64_t (this->v.i64/a.v.i64));
			case F32: return MValue(float   (this->v.f32/a.v.f32));
			case F64: return MValue(double  (this->v.f64/a.v.f64));
			default:  return MValue(uint8_t (this->v.u8 / a.v.u8)); // unreachable, but just in case
		}
	}

	inline MValue operator% (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("MOD: cannot get the modulus of lists\n");

		if (this->t != a.t)
			throw TYPE_ERROR("MOD", type_to_string(this->t), type_to_string(a.t));

		if (this->t == F64 || this->t == F32)
			throw MExcept("MOD: mod is inaccurate on floating point numbers\n");

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8 % a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16%a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32%a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64%a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8 % a.v.i8));
			case I16: return MValue(int16_t (this->v.i16%a.v.i16));
			case I32: return MValue(int32_t (this->v.i32%a.v.i32));
			case I64: return MValue(int64_t (this->v.i64%a.v.i64));
			default:  return MValue(uint8_t (this->v.u8 % a.v.u8)); // unreachable, but just in case
		}
	}

	inline MValue operator& (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("BAND: cannot perform bitwise and on lists\n");

		if (this->t == F32 || this->t == F64)
			throw MExcept("BAND: cannot perform bitwise and on floating point numbers\n");

		if (this->t != a.t)
			throw TYPE_ERROR("BAND", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8  & a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16 & a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32 & a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64 & a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8  & a.v.i8));
			case I16: return MValue(int16_t (this->v.i16 & a.v.i16));
			case I32: return MValue(int32_t (this->v.i32 & a.v.i32));
			case I64: return MValue(int64_t (this->v.i64 & a.v.i64));
			default:  return MValue(uint8_t (this->v.u8  & a.v.u8)); // unreachable, but just in case
		}
	}

	inline MValue operator| (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("BOR: cannot perform bitwise or on lists\n");

		if (this->t == F32 || this->t == F64)
			throw MExcept("BOR: cannot perform bitwise or on floating point numbers\n");

		if (this->t != a.t)
			throw TYPE_ERROR("BOR", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8  | a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16 | a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32 | a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64 | a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8  | a.v.i8));
			case I16: return MValue(int16_t (this->v.i16 | a.v.i16));
			case I32: return MValue(int32_t (this->v.i32 | a.v.i32));
			case I64: return MValue(int64_t (this->v.i64 | a.v.i64));
			default:  return MValue(uint8_t (this->v.u8  | a.v.u8)); // unreachable, but just in case
		}
	}

	inline MValue operator^ (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("BXOR: cannot perform bitwise xor on lists\n");

		if (this->t == F32 || this->t == F64)
			throw MExcept("BXOR: cannot perform bitwise xor on floating point numbers\n");

		if (this->t != a.t)
			throw TYPE_ERROR("BXOR", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return MValue(uint8_t (this->v.u8  ^ a.v.u8));
			case U16: return MValue(uint16_t(this->v.u16 ^ a.v.u16));
			case U32: return MValue(uint32_t(this->v.u32 ^ a.v.u32));
			case U64: return MValue(uint64_t(this->v.u64 ^ a.v.u64));
			case I8 : return MValue(int8_t  (this->v.i8  ^ a.v.i8));
			case I16: return MValue(int16_t (this->v.i16 ^ a.v.i16));
			case I32: return MValue(int32_t (this->v.i32 ^ a.v.i32));
			case I64: return MValue(int64_t (this->v.i64 ^ a.v.i64));
			default:  return MValue(uint8_t (this->v.u8  ^ a.v.u8)); // unreachable, but just in case
		}
	}

	inline bool operator== (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("EQ: cannot get equality of lists\n");

		if (this->t != a.t)
			throw TYPE_ERROR("EQ", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return (this->v.u8 ==a.v.u8);
			case U16: return (this->v.u16==a.v.u16);
			case U32: return (this->v.u32==a.v.u32);
			case U64: return (this->v.u64==a.v.u64);
			case I8 : return (this->v.i8 ==a.v.i8);
			case I16: return (this->v.i16==a.v.i16);
			case I32: return (this->v.i32==a.v.i32);
			case I64: return (this->v.i64==a.v.i64);
			case F32: return (this->v.f32==a.v.f32);
			case F64: return (this->v.f64==a.v.f64);
			default:  return false; // literally unreachable
		}
	}

	inline bool operator!= (MValue a) {
		if (this->is_list || a.is_list)
			throw MExcept("EQ: cannot get equality of lists\n");

		if (this->t != a.t)
			throw TYPE_ERROR("EQ", type_to_string(this->t), type_to_string(a.t));

		switch(a.t) {
			case U8 : return (this->v.u8 !=a.v.u8);
			case U16: return (this->v.u16!=a.v.u16);
			case U32: return (this->v.u32!=a.v.u32);
			case U64: return (this->v.u64!=a.v.u64);
			case I8 : return (this->v.i8 !=a.v.i8);
			case I16: return (this->v.i16!=a.v.i16);
			case I32: return (this->v.i32!=a.v.i32);
			case I64: return (this->v.i64!=a.v.i64);
			case F32: return (this->v.f32!=a.v.f32);
			case F64: return (this->v.f64!=a.v.f64);
			default:  return false; // literally unreachable
		}
	}
		
};
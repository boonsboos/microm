#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

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
	F64,
	LIST_U8,
	LIST_U16,
	LIST_U32,
	LIST_U64,
	LIST_I8,
	LSIT_I16,
	LIST_I32,
	LIST_I64,
	LIST_F32,
	LIST_F64
};

class MValue
{	
	Value   v;
	Type    t;
	
	// list stuff
	bool is_list   = false;
	static const size_t list_size = 1;
	Value l[list_size];

public:
	
	~MValue() {};

	MValue(); // makes U8 with value 0
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

	std::string to_string();

	inline std::ostream& operator<< (std::ostream &out) {
		return out << this->to_string();
	}
		
};
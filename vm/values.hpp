#pragma once

#include <cstdint>
#include <string>
#include <vector>

class MValue
{
public:
	virtual ~MValue();	
};

class MFloat : MValue
{
public:
	float v;
}

class MDouble : MValue
{
public:
	double v;
}

class MUChar : MValue
{
public:
	char v;
}

class MUShort : MValue
{
public:
	uint16_t v;
}

class MUInt : MValue
{
public:
	uint32_t v;
}

class MULong : MValue
{
public:
	uint64_t v;
}

class MIChar : MValue
{
public:
	int8_t v;
}

class MIShort : MValue
{
public:
	int16_t v;
}

class MIInt : MValue
{
public:
	int32_t v;
}

class MILong : MValue
{
public:
	int64_t v;
}

class MString : MValue
{
public:
	std::string v;
}

class MList : MValue
{
public:
	std::vector<MValue> v;
}
#pragma once

#include <iostream>
#include <vector>

#include "minst.hpp"

using std::vector;

// transforms the bytecode into instructions
class MLoader
{
	vector<MInst> instructions;
	size_t       idx;

	uint8_t  get_u8(vector<uint8_t> &s);
	uint64_t get_u64(vector<uint8_t> &s);
	uint32_t get_u32(vector<uint8_t> &s);
	uint16_t get_u16(vector<uint8_t> &s);
public:
	void load(std::string filename);
	inline vector<MInst> get_program() { return this->instructions; }
};
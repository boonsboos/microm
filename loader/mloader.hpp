#pragma once

#include <iostream>
#include <vector>

#include "minst.hpp"

using std::vector;

// transforms the bytecode into instructions
class MLoader
{
	vector<MInst> instructions;
public:
	void load(std::string filename);
	inline vector<MInst> get_program() { return this->instructions; }
};
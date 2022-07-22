#pragma once

#include <iostream>
#include <vector>

#include "values.hpp"

using std::string;
using std::vector;

class Microm
{
	MValue registers[16];
	vector<MValue> stack;

public:

	inline void dump_stack() {
		
	}

	// worked out in instructions.cpp
	void push(MValue v); // pushes Value v to the top of the stack
	void mov(int reg, MValue v); // moves into reg Value v
	MValue pop(); // pops value from top of stack
	MValue popr(int reg); // pops/deletes value from register
};
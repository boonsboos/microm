#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "mvalue.hpp"

using std::array;
using std::string;
using std::vector;

class Microm
{
	MValue registers[16];
	vector<MValue>    stack;

public:

	Microm() {
		for (int i = 0; i < 16; i++) {
			registers[i] = MValue();
		}
	}

	// utility
	inline void dump() {
		for (int i = 0; i < 16; i++) {
			if ((i + 1) % 4 != 0) // who needs aligning
				std::cout << "r" << i << ": " << registers[i].to_string() << " | ";
			else
				std::cout << "r" << i << ": " << registers[i].to_string() << "\n";
		}
	}

	// worked out in instructions.cpp
	void push(MValue v); // pushes Value v to the top of the stack
	void mov(int reg, MValue v); // moves into reg Value v
	MValue pop(); // pops value from top of stack
	MValue popr(int reg); // pops/deletes value from register
};
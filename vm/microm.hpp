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
	MValue         registers[16];
	vector<MValue> stack;

public:

	Microm() {
		for (MValue i : registers)
			i = MValue();
	}

	// utility
	inline void dump() {
		std::cout << "REGISTERS\n";
		for (int i = 0; i < 16; i++) {
			std::cout << "r" << i << ": " << registers[i].to_string() << "\n";
		}
	}

	inline void dump_with_stack() {
		std::cout << "REGISTERS\n";

		for (int i = 0; i < 16; i++) {
			std::cout << "r" << i << ": " << registers[i].to_string() << "\n";
		}

		std::cout << "STACK:\n";

		if (stack.size() == 0) {
			std::cout << "<empty>\n";
			return;
		}
		// from top of the stack
		for (size_t i = stack.size() - 1; i > 0; i--) {
			std::cout << i << ": " << stack[i].to_string() << "\n";
		}
	}

	// worked out in instructions.cpp
	void push(MValue v); // pushes Value v to the top of the stack
	void mov(int reg, MValue v); // moves into reg Value v
	MValue pop(); // pops value from top of stack
	MValue popr(int reg); // pops/deletes value from register
};
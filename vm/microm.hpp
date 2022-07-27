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

	~Microm() {};

	// utility
	inline void dump() {
		std::cout << "REGISTERS:\n";

		for (int i = 0; i < 16; i++) {
			std::cout << i << ": " << registers[i].to_string() << "\n";
		}	

		std::cout << "STACK:\n";

		if (!stack.size()) {
			std::cout << "<empty>\n";
			return;
		}
		// from top of the stack
		for (MValue i : stack) {
			std::cout << i.to_string() << "\n";
		}
	}

	// instructions | check ./instructions.cpp for implementation details
	// basic register ops
	void   mov(MValue v, int reg); // moves v into reg | TYPED
	MValue popr(int reg); // pops/deletes value from register and sets the value to (U8) 0
	void   copyr(int r, int s); // makes a copy of r in s
	// stack operations
	void   push(MValue v); // pushes Value v to the top of the stack | TYPED
	MValue pop(); // pops value from top of stack | BOUNDS CHECKED
	void   get(int idx, int reg); // copies the value at stack[idx] into reg | NOT BOUNDS CHECKED
	void   set(int idx, int reg); // sets the value at stack[idx] to reg | NOT BOUNDS CHECKED
	void   copy(); // copies top element | BOUNDS CHECKED
	void   swap(); // swaps top elements | BOUNDS CHECKED
	// mathematical operations
	// these can fail and will then throw an error
	void   add(int r, int s); // r + s | TYPED
	void   sub(int r, int s); // r - s | TYPED
	void   mul(int r, int s); // r * s | TYPED
	void   div(int r, int s); // r / s | TYPED
	void   mod(int r, int s); // r % s | TYPED
	void   neg(int r);        // -(r)  | TYPED
	// binary operations - prefixed with b- because apparently they are keywords in C++
	void   band(int r, int s);// r & s | TYPED
	void   bor(int r, int s); // r | s | TYPED
	void   bxor(int r, int s);// r ^ s | TYPED
	// logical operations - prefixed with l- for above reason
	void   land(int r, int s);//r && s | TYPED, returns U8 in r
	void   lor(int r, int s);// r || s | TYPED, returns U8 in r
	void   eq(int r, int s); // r == s | TYPED, returns U8 in r
	void   neq(int r, int s);// r != s | TYPED, returns U8 in r
	// list ops | notes/list.md for info
	void   list(int len_r, int type_r); // creates a new list with length in len_r and type in type_r | TYPED: len_r should be of type U64
	void   idx(int list_r, int idx); // puts the value int the list[idx] in r0, where list is a register | TYPED
	void   edit(int list_r, int idx, int value_r); // sets the value at list_r[idx] to value | TYPED
};
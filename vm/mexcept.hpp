#pragma once

#include <iostream>
#include <string>

using std::string;
using std::cerr;

// wrapper class for exceptions.
class MExcept
{
public:
	string e;

	MExcept(string e) { this-> e = e; }
};

inline MExcept TYPE_ERROR(string inst, string a, string b) {
	return MExcept(inst + ": type error - expected `" + a + "` but got `" + b + "`\n"); 
}

inline MExcept STACK_UNDERFLOW(string inst) {
	return MExcept(inst + ": stack underflow!\n");
}
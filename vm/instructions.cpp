#include "vm.hpp"
#include "mvalue.hpp"

#include <vector>

void Microm::push(MValue v)
{
	stack.push_back(v);
}

MValue Microm::pop()
{
	auto a = stack[stack.size() - 1];
	stack.pop_back();
	return a;
}

void Microm::mov(int reg, MValue v)
{
	registers[reg] = v;
}

MValue Microm::popr(int reg)
{
	return registers[reg];
	registers[reg] = MValue(uint8_t(0));
}
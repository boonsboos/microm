#include "microm.hpp"
#include "mvalue.hpp"
#include "mexcept.hpp"

#include <vector>

void Microm::mov(MValue v, int reg)
{
	registers[reg] = v;
}

MValue Microm::popr(int reg)
{
	return registers[reg];
	registers[reg] = MValue();
}

void Microm::copyr(int r, int s)
{
	registers[s] = registers[r];
}

void Microm::push(MValue v)
{
	stack.push_back(v);
}

MValue Microm::pop()
{
	if (!stack.size()) STACK_UNDERFLOW("pop");

	MValue a = stack[stack.size() - 1];
	stack.pop_back();
	return a;
}

void Microm::get(int idx, int reg)
{
	registers[reg] = stack[idx];
}

void Microm::set(int idx, int reg)
{
	stack[idx] = registers[reg];
}

void Microm::copy()
{
	if (stack.size() > 0)
		stack.push_back(stack[stack.size()-1]);
}

void Microm::swap()
{
	if (stack.size() > 1) {
		MValue a = this->pop();
		MValue b = this->pop();
		stack.push_back(a);
		stack.push_back(b);
	}
}

void Microm::add(int r, int s)
{
	try {
		registers[r] = (registers[r] + registers[s]);
		registers[s] = MValue();
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}

void Microm::sub(int r, int s)
{
	try {
		registers[r] = (registers[r] - registers[s]);
		registers[s] = MValue();
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}

void Microm::mul(int r, int s)
{
	try {
		registers[r] = (registers[r] * registers[s]);
		registers[s] = MValue();
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}

void Microm::neg(int r)
{
	try {
		registers[r] = -registers[r];
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}
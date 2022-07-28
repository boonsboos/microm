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

void Microm::div(int r, int s)
{
	try {
		registers[r] = (registers[r] / registers[s]);
		registers[s] = MValue();
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}

void Microm::mod(int r, int s)
{
	try {
		registers[r] = (registers[r] % registers[s]);
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

void Microm::band(int r, int s)
{
	try {
		registers[r] = (registers[r] & registers[s]);
		registers[s] = MValue();
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}

void Microm::bor(int r, int s)
{
	try {
		registers[r] = (registers[r] | registers[s]);
		registers[s] = MValue();
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}

void Microm::bxor(int r, int s)
{
	try {
		registers[r] = (registers[r] ^ registers[s]);
		registers[s] = MValue();
	} catch(MExcept exc) {
		std::cerr << exc.e;
		exit(1);
	}
}

void Microm::eq(int r, int s)
{
	if (registers[r] == registers[s]) {
		registers[r] = MValue(uint8_t(1));
	} else {
		registers[r] = MValue(uint8_t(0));
	}
	registers[s] = MValue();
}

void Microm::neq(int r, int s)
{
	if (registers[r] != registers[s]) {
		registers[r] = MValue(uint8_t(1));
	} else {
		registers[r] = MValue(uint8_t(0));
	}
	registers[s] = MValue();
}

void Microm::list(int len_r, int type_r)
{
	if (registers[len_r].t != U64) {
		std::cerr << TYPE_ERROR("LIST", "U64", type_to_string(registers[len_r].t)).e;
		exit(1);
	}

	uint64_t len = registers[len_r].v.u64;

	switch (registers[type_r].t) {
		case U8:  registers[0] = MValue(uint8_t(0),  len); break;
		case U16: registers[0] = MValue(uint16_t(0), len); break;
		case U32: registers[0] = MValue(uint32_t(0), len); break;
		case U64: registers[0] = MValue(uint64_t(0), len); break;
		case I8:  registers[0] = MValue(int8_t(0),   len); break;
		case I16: registers[0] = MValue(int16_t(0),  len); break;
		case I32: registers[0] = MValue(int32_t(0),  len); break;
		case I64: registers[0] = MValue(int64_t(0),  len); break;
		case F32: registers[0] = MValue(float(0),    len); break;
		case F64: registers[0] = MValue(double(0),   len); break;
		default: registers[0] = MValue(len); break;
	}
}
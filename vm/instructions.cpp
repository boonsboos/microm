#include "vm.hpp"
#include "values.hpp"

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
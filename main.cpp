#include "vm/microm.hpp"
#include "vm/mvalue.hpp"

int main(int argc, char **argv)
{
	Microm m = Microm();

	m.mov(MValue(uint32_t(70000)), 0);
	m.mov(MValue(uint32_t(10)), 1);
	m.add(0, 1);
	m.dump();
}
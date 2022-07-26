#include "vm/microm.hpp"
#include "vm/mvalue.hpp"

int main(int argc, char **argv)
{
	Microm m = Microm();

	m.mov(0, MValue(uint32_t(70000)));
	m.dump();
}
#include "vm/microm.hpp"
#include "vm/mvalue.hpp"
#include "loader/mloader.hpp"


int main(int argc, char **argv)
{

	MLoader l;
	l.load("test");

	// Microm m = Microm();

	// m.mov(MValue(uint8_t(10)), 0);
	// m.neg(0);
	// m.dump();
}
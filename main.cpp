#include "vm/microm.hpp"
#include "vm/mvalue.hpp"
#include "loader/mloader.hpp"


int main(int argc, char **argv)
{

	MLoader l;

	try {
		l.load("test");
	} catch(MExcept e) {
		std::cerr << e.e;
	}

	Microm m = Microm();
	m.run(l);
	// m.mov(MValue(uint8_t(10)), 0);
	// m.neg(0);
	m.dump();
	exit(0);
}
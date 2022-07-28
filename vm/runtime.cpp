#include "microm.hpp"

#include <vector>

#include "../loader/mloader.hpp"
#include "../loader/minst.hpp"

void Microm::run(MLoader m)
{
	this->program = m.get_program();

	for (MInst i : this->program)
	{
		switch(i.type) {
		#ifdef MDEBUG
			case DUMP: this->dump(); break;
		#endif
			case MOV:  this->mov(i.num, i.i1); break;
			case POPR: this->popr(i.i1); break;
			case COPYR:this->copyr(i.i1, i.i2); break;
		}
	}

}

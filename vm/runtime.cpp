#include "microm.hpp"

#include <vector>

#include "../loader/mloader.hpp"
#include "../loader/minst.hpp"

void Microm::run(MLoader m)
{
	this->program = m.get_program();

	for (MInst i : this->program)
	{
		//std::cout << i.to_string();

		switch(i.type) {
		#ifdef MDEBUG
			case DUMP: this->dump(); break;
		#endif
			case MOV:  this->mov(i.num, i.i1); break;
			case POPR: this->popr(i.i1); break;
			case COPYR:this->copyr(i.i1, i.i2); break;
			case PUSH: this->push(i.num); break;
			case POP:  this->pop(); break;
			case GET:  this->get(i.i1, i.i2); break;
			case SET:  this->set(i.i1, i.i2); break;
			case COPY: this->copy(); break;
			case SWAP: this->swap(); break;
			case ADD:  this->add(i.i1, i.i2); break;
			case SUB:  this->sub(i.i1, i.i2); break;
		}
	}

}

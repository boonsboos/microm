#include "minst.hpp"

#include "./vm/mvalue.hpp"

MInst::MInst(InstType t)
{
	this->type = t;
}

MInst::MInst(InstType t, int r1)
{
	this->type = t;
	this->i1 = r1;
}

MInst::MInst(InstType t, int r1, int r2)
{
	this->type = t;
	this->i1 = r1;
	this->i2 = r2;
}

MInst::MInst(InstType t, int r1, int r2, int r3)
{
	this->type = t;
	this->i1 = r1;
	this->i2 = r2;
	this->i3 = r3;
}

MInst::MInst(InstType t, MValue i)
{
	this->type = t;
	this->num = i;
}

MInst::MInst(InstType t, MValue i, int r1)
{
	this->type = t;
	this->num = i;
	this->i1 = r1;
}
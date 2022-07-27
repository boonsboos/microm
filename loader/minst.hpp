#pragma once

#include <cstdint>
#include <vector>

#include "./vm/mvalue.hpp"

using std::vector;

enum InstType {
#ifdef MDEBUG
	DUMP,
#endif
	MOV,
	POPR,
	COPYR
};

class MInst
{
public:
	InstType       type;
	Type           num;
	vector<MValue> input;

	MInst(InstType t) {
		this->type = t;
	}

	MInst(InstType t, Type n, vector<MValue> i) {
		this->type = t;
		this->num  = n;
		this->input= i;
	}
};
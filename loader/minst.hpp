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
	COPYR,
	PUSH,
	POP,
	GET,
	SET,
	COPY,
	SWAP,
	ADD,
	SUB
};

inline std::string inst_type_to_string(InstType t)
{
	switch(t) {
	#ifdef MDEBUG
		case DUMP : return "DUMP";
	#endif
		case MOV : return "MOV";
		case POPR: return "POPR";
		case COPYR:return "COPYR";
		case PUSH: return "PUSH";
		case POP:  return "POP";
		case GET:  return "GET";
		case SET:  return "SET";
		case COPY: return "COPY";
		case SWAP: return "SWAP";
		case ADD:  return "ADD";
		case SUB:  return "SUB";
		default: return "UNREACHABLE";
	}
}

class MInst
{
public:
	InstType type;
	MValue   num;  
	int      i1 = 0;
	int      i2 = 0;
	int      i3 = 0;

	MInst(InstType t); // dump, pop, dup, swap
	MInst(InstType t, int r1); // neg, popr
	MInst(InstType t, int r1, int r2); // copyr, add
	MInst(InstType t, int r1, int r2, int r3); // idx
	MInst(InstType t, MValue i); // push
	MInst(InstType t, MValue i, int r1); // mov, list

	inline std::string to_string() {
		return "MInst{" + inst_type_to_string(type) + "," + num.to_string() + "," + std::to_string(i1) + "," + std::to_string(i2) + "," + std::to_string(i3) + "}\n";
	}
};
#include "mloader.hpp"

#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "minst.hpp"

using std::string;
using std::ifstream;

inline uint8_t MLoader::get_u8(vector<uint8_t> &s)
{
	return s[this->idx++];
}

uint64_t MLoader::get_u64(vector<uint8_t> &s)
{
	return (uint64_t) (
		(uint64_t) get_u8(s)       | (uint64_t) get_u8(s) << 8  | 
		(uint64_t) get_u8(s) << 16 | (uint64_t) get_u8(s) << 24 |
		(uint64_t) get_u8(s) << 32 | (uint64_t) get_u8(s) << 40 | 
		(uint64_t) get_u8(s) << 48 | (uint64_t) get_u8(s) << 52
	);
}

uint32_t MLoader::get_u32(vector<uint8_t> &s)
{
	return (uint32_t) (
		(uint32_t) get_u8(s)       | (uint32_t) get_u8(s) << 8 | 
		(uint32_t) get_u8(s) << 16 | (uint32_t) get_u8(s) << 24
	);
}

uint16_t MLoader::get_u16(vector<uint8_t> &s)
{
	return (uint16_t) (get_u8(s) | (uint16_t) get_u8(s) << 8);
}

// just going to give you a heads-up:
// below is the most vile C++ code to ever see the light of day
void MLoader::load(string filename)
{
	ifstream file(filename);

	if (!file) {
		std::cerr << "failed to open " << filename << "\n";
		exit(1);
	}

	string contents = string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	vector<uint8_t> bytes; 

	for (char i : contents) {
		bytes.push_back((uint8_t) i);
	}

	while (idx < bytes.size())
	{
		uint8_t inst = get_u8(bytes); // instruction

		switch (inst) {
		#ifdef MDEBUG // if built with debug flag, enables dump instruction.
			case 0x00: 
				instructions.push_back(MInst(DUMP));
				break;
		#endif
			case 0x01: {
				uint8_t t = get_u8(bytes); // gets type
				switch(t) {
					case 0x00: // U8
						instructions.push_back(MInst(
							MOV,
							MValue(get_u8(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x01: // U16
						instructions.push_back(MInst(
							MOV,
							MValue(get_u16(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x02: // U32
						instructions.push_back(MInst(
							MOV,
							MValue(get_u32(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x03: // U64
						instructions.push_back(MInst(
							MOV,
							MValue(get_u64(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x04: // I8
						instructions.push_back(MInst(
							MOV,
							MValue((int8_t) get_u8(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x05: // I16
						instructions.push_back(MInst(
							MOV,
							MValue((int16_t) get_u16(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x06: // I32
						instructions.push_back(MInst(
							MOV,
							MValue((int32_t) get_u32(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x07: // I64
						instructions.push_back(MInst(
							MOV,
							MValue((int64_t) get_u64(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x08: // F32
						instructions.push_back(MInst(
							MOV,
							MValue((float) get_u32(bytes)),
							(int) get_u8(bytes)
						));
						break;
					case 0x09: // F64
						instructions.push_back(MInst(
							MOV,
							MValue((double) get_u64(bytes)),
							(int) get_u8(bytes)
						));
						break;
					default:
						throw MExcept("MLoader: unknown type! type > 0x09: " + std::to_string(t));
						break;
				}
				} break; // scope so compiler doesn't complain
			case 0x02:
				instructions.push_back(MInst(
					POPR,
					(int) get_u8(bytes)
				));
				break;
			case 0x03:
				instructions.push_back(MInst(
					COPYR,
					(int) get_u8(bytes),
					(int) get_u8(bytes)
				));
				break;
			case 0x04: {
				uint8_t t = get_u8(bytes); // gets type
				switch(t) {
					case 0x00: // U8
						instructions.push_back(MInst(
							PUSH,
							MValue(get_u8(bytes))
						));
						break;
					case 0x01: // U16
						instructions.push_back(MInst(
							PUSH,
							MValue(get_u16(bytes))
						));
						break;
					case 0x02: // U32
						instructions.push_back(MInst(
							PUSH,
							MValue(get_u32(bytes))
						));
						break;
					case 0x03: // U64
						instructions.push_back(MInst(
							PUSH,
							MValue(get_u64(bytes))
						));
						break;
					case 0x04: // I8
						instructions.push_back(MInst(
							PUSH,
							MValue((int8_t) get_u8(bytes))
						));
						break;
					case 0x05: // I16
						instructions.push_back(MInst(
							PUSH,
							MValue((int16_t) get_u16(bytes))
						));
						break;
					case 0x06: // I32
						instructions.push_back(MInst(
							PUSH,
							MValue((int32_t) get_u32(bytes))
						));
						break;
					case 0x07: // I64
						instructions.push_back(MInst(
							PUSH,
							MValue((int64_t) get_u64(bytes))
						));
						break;
					case 0x08: // F32
						instructions.push_back(MInst(
							PUSH,
							MValue((float) get_u32(bytes))
						));
						break;
					case 0x09: // F64
						instructions.push_back(MInst(
							PUSH,
							MValue((double) get_u64(bytes))
						));
						break;
					default:
						throw MExcept("MLoader: unknown type! type > 0x09: " + std::to_string(t));
						break;
				}
				} break;
			case 0x05:
				instructions.push_back(MInst(POP));
				break;
			case 0x06:
				instructions.push_back(MInst(
					GET,
					(int) get_u8(bytes),
					(int) get_u8(bytes)
				));
				break;
			case 0x07:
				instructions.push_back(MInst(
					SET,
					(int) get_u8(bytes),
					(int) get_u8(bytes)
				));
				break;
			case 0x08:
				instructions.push_back(MInst(COPY));
				break;
			case 0x09:
				instructions.push_back(MInst(SWAP));
				break;
		}
		
	}
}
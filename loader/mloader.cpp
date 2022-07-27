#include "mloader.hpp"

#include <fstream>
#include <string>

using std::string;
using std::ifstream;

void MLoader::load(string filename)
{
	ifstream file = ifstream(filename);

	while (!file.eof())
	{
		uint8_t byte = (uint8_t) file.get();
		switch (byte) {
		#ifdef MDEBUG
			case 0x00: 
				instructions.push_back(MInst(DUMP));
				break;
		#endif
			case 0x01:
				instructions.push_back(MInst(MOV, file.get(), ));
				break;
			case 0x02:
				instructions.push_back(MInst(POPR, file.get()));
			case 0x03:
				instructions.push_back(MINST(COPYR, 0))
		}
		
	}
}

Value leb_decode()
{

}
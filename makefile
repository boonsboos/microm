FLAGS := -O2 -std=c++17
OUT := -o microm.exe
SRC := main.cpp ./vm/vm.cpp

all:
	g++ $(FLAGS) $(OUT) $(SRC)
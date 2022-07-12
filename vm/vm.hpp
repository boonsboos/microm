#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

using std::array, std::string, std::vector;

class Microm
{
    array<string, 15>  regs;
    array<int64_t, 16> regi;
    array<double, 16>  regf;

    vector<string>   stacks;
    vector<int64_t>  stacki;
    vector<double>   stackf;

public:

    Microm();
    ~Microm();

    // utility functions
    void stack_underflow(string);
    void load_string(string);

    // instructions
    // moves value into register
    void movi(int, int64_t);
    void movf(int, double);
    // pops the value in register to the top of the stack
    void popi(int);
    void popf(int);
    // puts the top value on the stack in register
    void stori(int);
    void storf(int);
    // makes a copy of the top value on the stack
    void copyi();
    void copyf();
    // copies value in register b to another register b
    void rcopyi(int, int);
    void rcopyf(int, int);
    // moves value from register a to register b
    void rmovi(int, int);
    void rmovf(int, int);
    // writes value in register to filedescriptor
    void iwrite(int, int64_t);
    void fwrite(int, int64_t);
    void swrite(int, int64_t); // index in string stack, not register
};
#include <iostream>

#include "vm.hpp"

using std::cout, std::cerr;

Microm::Microm() {}
Microm::~Microm() {}

void Microm::stack_underflow(string inst)
{
    std::cerr << "stack underflow executing instruction " << inst << "\n";
    exit(1);
}

void Microm::load_string(string str)
{
    stacks.push_back(str);
}

void Microm::movi(int r, int64_t i)
{
    regi[r] = i;
}

void Microm::movf(int r, double f)
{
    regf[r] = f;
}

void Microm::popi(int r) 
{
    stacki.push_back(regi[r]);
    regi[r] = 0;
}

void Microm::popf(int r) 
{
    stackf.push_back(regf[r]);
    regf[r] = 0;
}

void Microm::stori(int r) 
{
    regi[r] = stacki.back();
    stacki.pop_back();
}

void Microm::storf(int r) 
{
    regf[r] = stackf.back();
    stackf.pop_back();
}

void Microm::iwrite(int r, int64_t fd)
{
    if (fd == 1) { 
        cout << regi[r];
        return;
    } else if (fd == 2) { 
        cerr << regi[r];
        return;
    }
}

void Microm::fwrite(int r, int64_t fd)
{
    if (fd == 1) { 
        cout << regf[r];
        return;
    } else if (fd == 2) { 
        cerr << regf[r];
        return;
    }
}

void Microm::swrite(int r, int64_t fd)
{
    if (fd == 1) { 
        cout << stacks[r];
        return;
    } else if (fd == 2) { 
        cerr << stacks[r];
        return;
    }
}
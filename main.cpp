#include <iostream>

#include "./vm/vm.hpp"

int main(int argc, char **argv)
{
    Microm m;

    m.load_string("write\n");
    m.swrite(0, 1);
}
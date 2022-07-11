# microm

a virtual machine with registers.

## infrastructure

microm has 2 types of registers: integer and floating point. they are numbered from 0 to 15 and are 32 bits wide.

each type has its own stack, which is read-only to the programmer. you cannot directly write to it, you must use stack manipulation to get the desired results. this may be annoying, but works better if microm is to be a compilation target.
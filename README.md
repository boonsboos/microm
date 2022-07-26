# microm

a virtual machine with registers and a stack.

## infrastructure

stack is mostly for lists, registers mostly for operands and math.

lists are strongly typed.

the bytecode format is TBD. there will be an assembly dialect for playing around.

## building
make sure you have meson installed.

```shell
meson build
cd build
meson compile
./microm
```
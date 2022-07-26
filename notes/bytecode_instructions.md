## bytecode
#### and the instruction set

since microm has different types, that all behave differently, it might be a good idea to have instructions behave differently for each type

similar to how WebAssembly does it:
`TYPE INSTRUCTION [OPERAND] [OPERAND]`

where TYPE is any of Microm's supported number types or a list of those types 
***
encoding TYPE would be done as follows: 
the highest bit of the byte is set.

therefore:
```
0x00 = U8
0x70 = U8 list
0x01 = U16
0x71 = U16 list
```
and so on.
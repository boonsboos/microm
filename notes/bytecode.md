## bytecode

since microm has different types, that all behave differently, it might be a good idea to have instructions behave differently for each type

similar to how WebAssembly does it:
`INSTRUCTION [TYPE] [OPERAND] [OPERAND]`

between [] means optional
 
where TYPE is any of Microm's supported number types or a list of those types.

you would then do stuff like `add 0 1` or `mov U8 0 128` or `copy`
***
encoding TYPE would be done as follows: 
```
0x00 = U8
0x01 = U16
...
0x09 = F64
```

numbers are just plainly encoded, just as byte arrays; no LEB128 jank.

do note the bytes are encoded in little endian format
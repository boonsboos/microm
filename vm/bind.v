module vm

#include <stdio.h>

// declarations for the standard C functions that Microm can call
fn C.open(pathname &u8, flags int) int
fn C.close(fd int) int
fn C.read(fd int, buf voidptr, count u32) int // using V's os.fd_read would be easier
fn C.write(fd int, buf voidptr, count u32) int
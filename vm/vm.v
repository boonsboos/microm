module vm

pub type Value = string | i8 | i16 | int |
				i64 | u8 | u16 | u32 | 
				u64 | f32 | f64 | []Value
// it looks like nested arrays are supported, but they are not.
// maybe in the future.

[heap]
pub struct Microm {
mut:
	stack []Value
}

[noreturn]
fn stack_underflow(op string) {
	eprint('stack underflow in $op\n')
	exit(1)
}

[noreturn]
fn type_error(op string, expect string, real string) {
	eprint('$op: expected `$expect`, got `$real`\n')
	exit(1)
}

[noreturn]
fn invalid_peek() {
	eprint('this should never happen!\n')
	exit(1)
}

[noreturn]
fn nested_arr() {
	eprint('nested arrays are not supported yet\n')
	exit(1)
}
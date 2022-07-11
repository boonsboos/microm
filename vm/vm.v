module vm

[heap]
pub struct Microm {
mut:
	regs   []string // constant string register
	regf   []f32 = []f32{len: 16} // float registers
	regi   []int = []int{len: 16} // int registers
	stackf []f32 // read only float stack
	stacki []int // read only int stack
}

fn (m Microm) stack_underflow(inst string) {
	eprintln('stack underflow executing $inst')
	exit(1)
}
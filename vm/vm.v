module vm

pub type Number = f32 | int

pub struct Microm {
mut:
	regs  []string // only touched at program load time
	regf  []f32 = []f32{len: 16} // float registers
	regi  []int = []int{len: 16} // int registers
	stack []Number // read only
}
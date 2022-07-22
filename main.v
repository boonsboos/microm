module main

import vm

fn main() {

	// m.push('bup') 
	// m.push(1)
	// m.open()
	// dump(m)
	// m.close()

	mut m := vm.Microm{}
	m.push('bup')     // bup
	m.push(0)         // bup 0
	m.open()          // fd
	m.push(u32(5))    // fd 1 5
	m.read()          // fd aasdf
	m.dump_stack()
	m.pop()           // fd
	m.close()         // result
	m.pop()           // 
	m.push(1)         // fd 1
	m.push('assdf\n') // fd assdf\n
	m.push(u32(6))    // fd assdf\n 6
	m.write()         // fd written
	m.pop()			  // fd
	m.close()         // result
	m.pop()           //
}
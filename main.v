module main

import vm

fn main() {
	mut instance := vm.Microm{}

	instance.movi(69, 0)
	instance.movf(42.0, 0)
	instance.popf(0)
	instance.popi(0)
	instance.stori(1)
	instance.storf(1)
	println(instance)
}
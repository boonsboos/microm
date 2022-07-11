module vm

[direct_array_access]
pub fn (mut m Microm) movi(i int, reg u8) {
	m.regi[reg] = i
}

[direct_array_access]
pub fn (mut m Microm) movf(f f32, reg u8) {
	m.regf[reg] = f
}

[direct_array_access]
pub fn (mut m Microm) popi(reg u8) {
	m.stack << Number(m.regi[reg])
	m.regi[reg] = 0
}

[direct_array_access]
pub fn (mut m Microm) popf(reg u8) {
	m.stack << Number(m.regf[reg])
	m.regf[reg] = 0.0
}
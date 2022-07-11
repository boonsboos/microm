module vm

// puts the given value into the given register
[inline; direct_array_access]
pub fn (mut m Microm) movi(i int, reg u8) {
	m.regi[reg] = i
}

[inline; direct_array_access]
pub fn (mut m Microm) movf(f f32, reg u8) {
	m.regf[reg] = f
}

// puts the value in the given register to the top of the stack
[inline; direct_array_access]
pub fn (mut m Microm) popi(reg u8) {
	m.stacki << m.regi[reg]
	m.regi[reg] = 0
}

[inline; direct_array_access]
pub fn (mut m Microm) popf(reg u8) {
	m.stackf << m.regf[reg]
	m.regf[reg] = 0.0
}

// puts the top value of the stack in the given register 
[inline; direct_array_access]
pub fn (mut m Microm) stori(reg u8) {
	if m.stacki.len == 0 { m.stack_underflow('stori') }
	m.regi[reg] = m.stacki.pop()
}

[inline; direct_array_access]
pub fn (mut m Microm) storf(reg u8) {
	if m.stackf.len == 0 { m.stack_underflow('storf') }
	m.regf[reg] = m.stackf.pop()
}

// duplicates the value on top of the stack
[inline; direct_array_access]
pub fn (mut m Microm) copyi() {
	m.stacki << m.stacki[m.stacki.len - 1]
}

[inline; direct_array_access]
pub fn (mut m Microm) copyf() {
	m.stackf << m.stackf[m.stackf.len - 1]
}

// copies value in reg into reg2
[inline; direct_array_access]
pub fn (mut m Microm) rcopyi(reg u8, reg2 u8) {
	m.regi[reg2] = m.regi[reg]
}

[inline; direct_array_access]
pub fn (mut m Microm) rcopyf(reg u8, reg2 u8) {
	m.regf[reg2] = m.regf[reg]
}

// moves the value in reg to reg2
[inline; direct_array_access]
pub fn (mut m Microm) rmovi(reg u8, reg2 u8) {
	m.rcopyi(reg, reg2)
	m.regi[reg] = 0
}

[inline; direct_array_access]
pub fn (mut m Microm) rmovf(reg u8, reg2 u8) {
	m.rcopyf(reg, reg2)
	m.regf[reg] = 0
}
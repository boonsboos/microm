module vm

[inline]
pub fn (mut m Microm) push(v Value) {
	m.stack << v
}

pub fn (mut m Microm) dump_stack() {
	print('Stack size: $m.stack.len\nStack: ')
	println(m.stack)
}

[inline]
pub fn (mut m Microm) pop() Value {
	if m.stack.len > 0 {
		return m.stack.pop()
	}
	stack_underflow('pop')
}

[inline]
pub fn (mut m Microm) dup() {
	if m.stack.len > 0 {
		m.stack << m.stack[m.stack.len-1]
		return
	}
	stack_underflow('dup')
}

[inline; direct_array_access]
fn (mut m Microm) peek(top_offset int) Value {
	if top_offset < 0 { invalid_peek() }
	return m.stack[m.stack.len-1-top_offset]
}

// converts the top of the stack to a list of the type of the top element
[inline]
pub fn (mut m Microm) toarr() {
	m.push([m.pop()])
}

// takes the value type of the top of the stack, and the value below it for size.
// `a b -- c`
// where c is an array of type a with capacity b with element 0 initialised with its default value of 0 or '' (empty string)
[inline]
pub fn (mut m Microm) newarr() {
	a := m.pop() // array type
	s := m.pop() // size
	match true {
		a is string { m.push([]Value{len: 1, cap: s as int, init: ''}) }
		a is i8     { m.push([]Value{len: 1, cap: s as int, init: i8(0)} ) }
		a is i16    { m.push([]Value{len: 1, cap: s as int, init: i16(0)}) }
		a is int    { m.push([]Value{len: 1, cap: s as int, init: int(0)}) }
		a is i64    { m.push([]Value{len: 1, cap: s as int, init: i64(0)}) }
		a is u8     { m.push([]Value{len: 1, cap: s as int, init: u8(0)} ) }
		a is u16    { m.push([]Value{len: 1, cap: s as int, init: u16(0)}) }
		a is u32    { m.push([]Value{len: 1, cap: s as int, init: u32(0)}) }
		a is u64    { m.push([]Value{len: 1, cap: s as int, init: u64(0)}) }
		a is f32    { m.push([]Value{len: 1, cap: s as int, init: f32(0.0)}) }
		a is f64    { m.push([]Value{len: 1, cap: s as int, init: f64(0.0)}) }
		else { 
			nested_arr()
		}
	}
}

// appends the element on top of the stack to the array below it
[inline]
pub fn (mut m Microm) arr_push() {
	mut arr := m.peek(1) as []Value
		ele := m.peek(0)

	// TODO: optimize this
	if arr[0].type_name() == ele.type_name() {
		arr << m.pop()
		m.stack[m.stack.len-1] = arr
	} else {
		type_error('arr_append', arr[0].type_name(), ele.type_name())
	}
}

[inline]
pub fn (mut m Microm) arr_pop() {
	mut arr := m.peek(0) as []Value
	arr.pop()
}

pub fn (mut m Microm) arr_idx() {
	mut arr := m.peek(1) as []Value
	idx := m.pop() 
	m.push(arr[idx as int])
}

// takes amount of bytes to read
// a b -- c
// where a is the fd, b is the amount of bytes to read
// c is a string
pub fn (mut m Microm) read() {
	// it's necessary to duplicate this, otherwise the function is ran more times
	cnt := m.pop()
	m.dup() // keep the fd there so you can close it later
	fd := m.pop()
	unsafe {
		mut buf := malloc(int(cnt as u32) + 1)
		b := C.read(fd as int, buf, cnt as u32)
		if b < 0 {
			free(buf)
			m.push('')
			return
		}

		buf[b] = 0
		m.push(tos(buf, b))
		free(buf)
	}
	
}

pub fn (mut m Microm) write() {
	cnt := m.pop()
	buff := m.pop()
	m.dup() // duplicate fd
	fd := m.pop()
	buf := buff as string
	m.push(C.write(fd as int, buf.str, cnt as u32))
}

// opens a file, takes flags from the top, path from top - 1
// `a b -- c`
// where c is the file descriptor
pub fn (mut m Microm) open() {
	flags := m.pop()
	path := m.pop()
	if path is string { m.push(C.open(path.str, flags as int)) }
	else { type_error('open', 'string', path.type_name()) }
}

// closes the file descriptor
pub fn (mut m Microm) close() {
	fd := m.pop()
	if fd is int { m.push(C.close(fd as int)) }
	else { type_error('close', 'int', fd.type_name()) }
}
## lists
declaring them C style?

eg: providing a length, and a type, then using a newlist instruction?

should they be able to grow and should there be a flag for growability?

it seems to be the easier option; what i would have to do is add the following things to MValue:
* `bool` is_list
* `int` list_size <- this should be set to 0 OR 1, see what works
* `MValue[list_size]` l;

instead of internally using a vec for example,

pros:
- gives microm (C style) strings for free
- C style arrays means ability to expand into FFI

cons:
- will increase the memory usage by at least 16 bytes/item if not a list
- will add more constructors

should lists be allocated on Microm's stack?
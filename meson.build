project('microm', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

vm = ['vm/instructions.cpp', 'vm/mvalue.cpp']
loader = ['loader/mloader.cpp']

executable('microm',
           'main.cpp', vm, loader)

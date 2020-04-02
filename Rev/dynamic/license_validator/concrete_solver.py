#!/usr/bin/env python2.7
"""
concrete_solver.py

    Used to concretely find a key for the license
    validator without the need of symbolic reasoning.
"""

import re
from pwn import *

# open binary, find target of interest
binary = ELF("./validator")
checkLicense = binary.symbols["checkLicense"]
print("checkLicense address: {}".format(hex(checkLicense)))

# disassemble the function and distillate raw output
func_disasm = binary.disasm(checkLicense, 300).split()
cmp_vals = [
    func_disasm[idx + 1]
    for idx, token in enumerate(func_disasm)
    if token == "3c"
]

print(cmp_vals)

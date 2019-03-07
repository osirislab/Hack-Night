#!/usr/bin/env python
from z3 import *

s = Solver()
alpha = Int("alpha")

op1 = alpha + 0x45
op2 = op1 - 0x1a4
op3 = op2 - 1
op4 = op3 + 0x7b
op5 = op4 - 0x1a4
op6 = op5 + 0x1a4
op7 = op6 - 0x7
op8 = op7 - 0x539
op9 = op8 + 5
op10 = op9 - 8
op11 = op10 + 0x45

s.add(op11 == 0x539)

assert(s.check())
print s.model()[alpha]

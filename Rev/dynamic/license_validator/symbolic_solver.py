#!/usr/bin/env python3
"""
symbolic_solver.py

    Demonstrates how we can crack the license validator automatically
    with Manticore's symbolic execution engine.

"""

from manticore.native import Manticore

m = Manticore("./validator")
m.verbosity(1)


@m.hook(0x400d24)
def hook(state):
    cpu = state.cpu
    print("Reached failed path")

    with m.locked_context() as context:
        res = "".join(map(chr, state.solve_buffer(cpu.RAX, 4)))
        print(res)
        context["count"] += 1


if __name__ == "__main__":
    m.run()

#!/usr/bin/env python3.6
"""
pwnable - collision challenge

    $ python win.py

    Solves collision challenge from pwnable.kr,
    using symbolic execution to determine edge cases that
    can trigger a hash collision.

"""
from manticore.native import Manticore
from manticore.core.smtlib import operators

m = Manticore("./col", ["+" * 20])
m.verbosity(2)

m.context["solution"] = None
m.context["argv1"] = None


@m.init
def init(initial_state):
    """ define constraints for symbolic ARGV before execution """

    # determine argv[1] from state.input_symbols by label name
    argv1 = next(sym for sym in initial_state.input_symbols if sym.name == "ARGV1")
    if argv1 is None:
        raise Exception("ARGV was not made symbolic")

    # apply constraint for only ASCII characters
    for i in range(20):
        initial_state.constrain(
            operators.AND(ord(" ") <= argv1[i], argv1[i] <= ord("}"))
        )

    # store argv1 in global state
    with m.locked_context() as context:
        context["argv1"] = argv1


# add fail_state callback to abandon
# paths we don't care about
def fail_state(state):
    print("Fail state! Abandoning.")
    state.abandon()

for addr in [0x400C2F, 0x400BE7, 0x400BAC]:
    m.add_hook(addr, fail_state)


@m.hook(0x400BA6)
def skip_syscalls(state):
    """ skip error-checking syscalls """
    state.cpu.EIP = 0x400BFA


@m.hook(0x400C1C)
def success_state(state):
    """ since input is symbolicated in argv, we search in
    state.input_symbols to find the label """
    with m.locked_context() as context:
        context["solution"] = state.solve_one(context["argv1"], 20)
    m.kill()



# run Manticore, and print solution
m.run()
print("EDGE CASE: ", m.context["solution"])

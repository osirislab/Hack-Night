#!/usr/bin/env python
from manticore import Manticore

m = Manticore("./strops.bin")

m.context['flag'] = ""

@m.hook(0x40076a)
def hook(state):
    buffer_addr = state.cpu.RSI
    state.cpu.write_bytes(buffer_addr, "a" * 50)
    state.cpu.EIP = 0x40076f

@m.hook(0x400798)
def hook(state):
    m.context['flag'] += chr(state.cpu.EDX)
    state.cpu.EAX = state.cpu.EDX

@m.hook(0x4007b9)
def hook(state):
    print(m.context['flag'])
    m.terminate()

@m.hook(0x40079c)
def hook(state):
    state.abandon()

m.run()

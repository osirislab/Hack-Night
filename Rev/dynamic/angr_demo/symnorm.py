#!/usr/bin/env python3
import angr
import claripy

def main():
    proj = angr.Project("./normal")
    find = [0x40079b]
    avoid = [0x400971]
    
    #answer_chars = [claripy.BVS('input_%d' % i, 8) for i in range(25)]
    #answer = claripy.Concat(*answer_chars + [claripy.BVV(b'\n')])
    
    state = proj.factory.entry_state()
    
    sm = proj.factory.simulation_manager(state)
    sm.explore(find=find, avoid=avoid)
    print(sm.found[0].posix.dumps(0))
main()

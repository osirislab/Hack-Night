#!/usr/bin/env python3
import angr
import claripy

def main():
    proj = angr.Project("./normal")
    find = [0x40079b]
    avoid = [0x400971]
    
    answer_chars = [claripy.BVS('input_%d' % i, 8) for i in range(25)]
    answer = claripy.Concat(*answer_chars + [claripy.BVV(b'\n')])
    
    state = proj.factory.full_init_state(
            args = ["./normal"],
            stdin=answer, 
            add_options={angr.options.LAZY_SOLVES});
    
    for k in answer_chars:
        state.solver.add(k > 65)
        state.solver.add(k < 122)
    
    sm = proj.factory.simulation_manager(state)
    #sm.explore(find=find, avoid=avoid)
    sm.run()
    
    out = b''
    for pp in sm.deadended:
        print(pp)
        out = pp.posix.dumps(0)
        print(out)

main()

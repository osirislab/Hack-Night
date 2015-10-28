import sys, os, stat

# seq are the bytes you want to replace
# Ex: seq = "\xBB\x08\x00\x00\x00\xEB\x14\x0F\x1F\x40\x00\x8B\x48\x2C\x39\xD9"
seq = ""

# rep_seq are the bytes you want to replace it with
rep_seq = ""

def main():
    if len(sys.argv) < 1:
        print "[*] Usage: %s <program>"
        return

    file_in  = sys.argv[1]

    with open(file_in, "rb") as f:
        prog = f.read()

    prog = prog.replace(seq, rep_seq)

    with open(file_in, "wb") as f:
        f.write(prog)

    st = os.stat(file_in)
    os.chmod(file_in, st.st_mode | stat.S_IEXEC)

if __name__ == "__main__":
    main()


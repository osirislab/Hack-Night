import re

password = raw_input("What is the password?: ")

if not re.match(r'^([a-z0-9\_\:])+$', password):
    print "[Failed Check 1]\n"
    exit(-1)

appa = [[ord(c) for c in x] for x in password.split(":")]

if len(appa) != 3:
    print "[Failed Check 2]\n"
    exit(-1)

if appa[0][::-1] != appa[0]:
    print "[Failed Check 3]\n"
    exit(-1)

sorted_part = sorted(appa[1])
if sorted_part != [95, 95, 100, 100, 101, 101, 109, 110, 111, 111, 115, 117, 121]:
    print "[Failed Check 4]\n"
    exit(-1)

if appa[2][0] - appa[2][7] != -2 \
        or appa[2][1] ^ appa[2][6] != 0 \
        or appa[2][2] * appa[2][5] != 9797 \
        or appa[2][3] + appa[2][4] != 198 \
        or appa[2][4] % appa[2][3] != 98 \
        or appa[2][5] + appa[2][2] != 198 \
        or appa[2][6] * appa[2][1] != 10201 \
        or appa[2][7] ^ appa[2][0] != 2:
    print "[Failed Check 5]\n"
    exit(-1)

print "Successfully passed every check!\n"

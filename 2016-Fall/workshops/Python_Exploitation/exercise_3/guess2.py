#!/usr/bin/python
import sys
import random

flag = "flag{XXXXXXXXXXXXXXXX}"

x = random.randrange(101)

resp = raw_input("What's my secret?\n")

try:
    y = int(resp)
except:
    print "kek\n"
    sys.exit()

if y==x:
    print "YOU DID IT! Here's the flag: " + flag + "\n"
    sys.exit()
else:
    print "kek\n"
    sys.exit()

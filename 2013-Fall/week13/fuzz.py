#Written by Evan Jensen (wontonslim@github)

import subprocess
from random import randint
from sys import argv

FILENAME = argv[1]
BYTESTOCHANGE=1 #change this many bytes per play
crashcase=0

while True:
    f = open(FILENAME,'r').read()


    low  = 200
    high = len(f)

    bytes = [i for i in f] #this is the file in memory as a chr array

    for i in range(BYTESTOCHANGE): #change random bytes to random vals
        randByte = chr(randint(0,0xff))
        bytes[randint(low,high)] = randByte
        
    newdata = ''.join(bytes)  #coalesce the bytes
    
    open(FILENAME,'w').write(newdata) #write back the file with changed bytes

    returnVal=subprocess.call(['mplayer','./'+FILENAME]) #does it crash?
    
    if(returnVal!=0):#zomg something interesting
        file(FILENAME+'.crash_'+str(crashcase),'w').write(newdata)#save data
        crashcase+=1
        print "ZOMG SOMETHING HAPPENED U GUYS!"



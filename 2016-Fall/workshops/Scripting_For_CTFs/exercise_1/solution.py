# NOTE: This is not the complete solution. This is just some code to get you started.

import socket

the_connection = socket.socket()
the_connection.connect(("misc.chal.csaw.io", 8000))

data = the_connection.recv(1024)
this_list = data.split("\n")
the_first_thing = this_list[0]
the_fist_thing = float(the_first_thing.replace("$", ""))
print the_fist_thing, type(the_first_thing)

#print "This is the shit the server gave us: ", data

#print "I am going to send the server \"0\""
#the_connection.send("0\n")

#data = the_connection.recv(1024)
#print "This is the shit the server gave us: ", data

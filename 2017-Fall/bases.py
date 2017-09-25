from socket import socket, AF_INET, SOCK_STREAM

s = socket(AF_INET, SOCK_STREAM)
s.connect(('216.165.2.56',9001))
s.recv(1024)
data = s.recv(1024)
print data

base = data[data.find('[')+1:data.find(']')]
num = data[data.find('(')+1:data.find(')')]
target = data[data.find('{')+1:data.find('}')]
print 'Base: ' + base
print 'Num: ' + num
print 'Target: ' + target

s.close()

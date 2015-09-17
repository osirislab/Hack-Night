import socket, ping
from struct import unpack, pack

my_ip = socket.gethostbyname(socket.gethostname())
print "My computer IP address:", my_ip
my_deets = socket.gethostbyname_ex(socket.gethostname())
print "My computer details:", my_deets

subnet_mask = "255.255.255.0"

def ip2long(ip):
    """
    Convert a long to IP string
    """
    return unpack(">L", socket.inet_aton(ip))[0]

def long2ip(ip):
    """
    Convert an IP string to long
    """
    return socket.inet_ntoa(pack('!L', ip))

addr = ip2long(my_ip)
mask = ip2long("255.255.255.0")
prefix = addr & mask

print "Base address for network", long2ip(prefix)

all_computers = ip2long("255.255.255.255")
num_computers = all_computers ^ mask

for ip_suffix in range(num_computers):
    test_ip = long2ip(prefix + ip_suffix)
    try:
        ping.quite_ping(test_ip, count=3)
        print "[+] Host is there:", test_ip
    except:
        print "[-] Host not there:", test_ip


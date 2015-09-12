# Interacting with Computers on Networks

## Slides
<link>

## Additional Resources
* [Introduction to Networking](http://www.net-intro.com/) (Recommended reading
* [Using NetCat](https://www.digitalocean.com/community/tutorials/how-to-use-netcat-to-establish-and-test-tcp-and-udp-connections-on-a-vps)
* [Using NMAP Part 1](https://www.youtube.com/watch?v=Bn36zoApLm4)
* [Using NMAP Part 2](https://www.youtube.com/watch?v=nr10P55AlKc)

## Things to Try
### Setup
Please checkout the setup section [here]() to be able to replicate the things to try

### Try it out
Note: When we tell you to type a command, disregard everything before the `#`. You should already see something similar in your terminal.
Open up a terminal (press ctrl+alt+t or click on the black icon on the top of the screen) and type:
```bash
ping 8.8.8.8
```
This command will try to talk to Google's Public DNS if you start seeing something like this:
```bash
root@kali:~# ping 8.8.8.8
PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
64 bytes from 8.8.8.8: icmp_req=1 ttl=128 time=2.93 ms
64 bytes from 8.8.8.8: icmp_req=2 ttl=128 time=2.91 ms
64 bytes from 8.8.8.8: icmp_req=3 ttl=128 time=3.08 ms
64 bytes from 8.8.8.8: icmp_req=4 ttl=128 time=2.82 ms
64 bytes from 8.8.8.8: icmp_req=5 ttl=128 time=2.80 ms
```
Then you know that you are both connected to the Internet and Google's DNS Server is up :D

If you want to see the path that your traffic takes from your computer to Google (what routers it goes to) try this:
```bash
root@kali:~# traceroute 8.8.8.8
traceroute to 8.8.8.8 (8.8.8.8), 30 hops max, 60 byte packets
 1  172-16-76-2.DYNAPOOL.NYU.EDU (172.16.76.2)  0.234 ms  0.127 ms  0.141 ms
 2  * * *
...
```
Note: you might get a lot of asterisks in your command output, that is most likely because one of the routers your traffic visits prevents you from doing `traceroute` on them.

Netcat was also talked about during Hack Night and it is a really neat tool. To test out how it works try this:
1. Type this command:
```
root@kali:~# nc www.google.com 80
```
2. Once you hit enter, it should look like it is trying to do something. This means that you are connected to Google and it is waiting for you to tell it to do something. So let's tell it to do something. Type the following and hit enter:
```
GET /
```
3. You should now see a bunch of HTML code streaming down your screen. You just visited Google's homepage! This is basically what your browser does everytime you tell it to get a page :D

Another cool thing to try is opening another terminal window (press ctrl+shift+t) and typing:
```
root@kali:~# nc -l -p 1337 127.0.0.1
```
And then click on the previous terminal window you were in and type:
```
root@kali:~# nc 127.0.0.1 1337
```
And then start typing random words. Now check back at the new tab you opened. You should start seeing the same words poping up there.

Essentially what you did was open a port on the localhost IP address (127.0.0.1 aka your computer). Netcat was then listening for any connections made to it. Once you connected to it and sent it somethings it printed them out. To stop them press ctrl+c in both terminal windows.

Lastly, there was another cool tool called Nmap that was talked about. To test this out first have one terminal window open and type the same command from the last section:
```
root@kali:~# nc -l -p 1337 127.0.0.1
```
In the other window type:
```
root@kali:~# nmap -v -sT -p-2000 127.0.0.1
```
You should then see something similar to the follow:
```
Starting Nmap 6.47 ( http://nmap.org ) at 2015-09-12 16:23 EDT
Initiating Connect Scan at 16:23
Scanning localhost (127.0.0.1) [2000 ports]
Discovered open port 111/tcp on 127.0.0.1
Discovered open port 1337/tcp on 127.0.0.1
Completed Connect Scan at 16:23, 0.03s elapsed (2000 total ports)
Nmap scan report for localhost (127.0.0.1)
Host is up (0.0014s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 1998 closed ports
PORT     STATE SERVICE
111/tcp  open  rpcbind
1337/tcp open  waste

Read data files from: /usr/bin/../share/nmap
Nmap done: 1 IP address (1 host up) scanned in 0.08 seconds
           Raw packets sent: 0 (0B) | Rcvd: 0 (0B)
```
The command tells nmap to try to connect to all ports 1 to 2000 and it will report back with its results.
Notice that nmap found the 1337 port open? That is because you opened it yourself!

If you followed along, you should by now have a good idea about what tools professionals use to test networks :D


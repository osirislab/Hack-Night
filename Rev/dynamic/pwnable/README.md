# pwnable - collision challenge

> Daddy told me about cool MD5 hash collision today.
> I wanna do something like that too!
> 
> See challenge: http://pwnable.kr/play.php

This challenge involved adding a binary that required a 20-byte input, which fed to a `check_password`
function that determined if it was equal to a local variable, `hashcode`.

The concrete solution for this challenge would be to induce a hash collision by doing some math 
and figuring out integers that are in total equal to the value in `hashcode`, 0x21DD09EC.

With Manticore, we can instead have a solver compute concrete inputs that satisfy the constraint for the path that reveals
the flag. Through symbolic execution, we can have various edge cases that causes a hash collision and triggers the code path,
so in order to combat unreadable characters, we can constrain the result to include only valid ASCII characters.

```
$ python test.py
...
EDGE CASE: b'\xf5\x15^\x80\xfc?\x01\xd7@\xe1{C@\xfd\xfeB{\xd5\x02D'

$ ./col `echo -n -e "\xf5\x15^\x80\xfc?\x01\xd7@\xe1{C@\xfd\xfeB{\xd5\x02D"`
daddy! I just managed to create a hash collision :)
```

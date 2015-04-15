## Exploitation Part 1

### Part 1 - Straight up Overflow
Changing Stack Based Variables with a Buffer Overflow
Task - Get authenticated

### Part 2 - Change Saved EIP
Changing Program Execution Flow with Stack Based Buffer Overflow
Task - Make the program execute code that it would otherwise would not have executed

### Part 3 - Execute Shellcode
Changing Program Execution Flow by Returning to User Controlled Data with a Stack Based Buffer Overflow
Task - Make the program execute code (shellcode) by tricking the program into thinking that your input is a function pointer

### Part 4 - ROP
Changing Program Execution Flow by Chaining Together Existing Code from the Program with a Stack Based Buffer Overflow
Task - Make the program execute certain functions in a sequential order

### Part 5 - Return to Libc
Changing Program Execution Flow by Performing a Return To Libc attack with a Stack Based Buffer Overflow
Task - Modify the program's GOT in order to trick the program into calling a series of ROP gadgets which end up spawning a shell

# Risky Python
There are some dangerous things that exist in Python that we want to avoid.

Two of these are the function `eval()` and the statement exec.

`eval()` interprets a string as code, essentially allowing a Python program to run Python code within itself. It evalutes an expression and returns the return value.

`x = eval(2+2)` stores `4` in `x`. `eval()` also has access to all the already defined variables and existing functions. Essentially if it's an expression, `eval()` can evaluate it.

`exec` is similar except it allows for the execution of statements and does not return anything.

`exec "print 'asdf'"` will simply print `asdf`.

Now although it may seem simple, and it is, what happens when we allow user input to go into `eval()` or `exec`.

For example, the `input()` function takes user input and runs it through `eval()`. It's basically `eval(raw_input())`.

How could `input()` be exploited to gain a shell on the system? We can't import other modules with the import keyword, but is there some way that we can import other modules without using the keyword?

The answer is surprisingly, yes.

`__import__('math')` will import the module and return it. Using that we can bring other code into the currently running script meaning we can bring things like the os module or even the code module to allow for higher level access.

This `__import__()` trick can be used to take advantage of most `eval()`s that accepted unfiltered user input.

Two other functions that can be used are the `locals()` and `globals()` functions.

These functions allow us to see and set currently existing variables.

###### Python introduction by Kevin Chung

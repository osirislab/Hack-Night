# Intro to Python // Setup
Python is one of the most popular programming languages in the world. It is a great introductory language praised for it's readability, ease of use, and versatility.
## Setup
You can download Python at [the Python website](https://www.python.org/downloads/), but if you use Linux, OSX, or something in that vein, you probably have a version of Python installed. You can go into your terminal and type in `python` to drop into the Python interpreter.

If you're on Windows, download Python, install it, and find the IDLE program in your start menu. Run IDLE and you will find a similar environment.

From within the Python interpreter we can interact with Python and play with code immediately. The interpreter can act as a playground for our code and by entering code and hitting Enter, we can immediately see the results of our code.
## First Steps
For example, try entering `2 + 2` and hit enter. If you do not get back `4`. Standard math right?

Here we have two `2`'s. They are known to computer scientists as integers. We also have the `+` sign. This is known to computer scientists as an operator.

Besides addition, we can do all sorts of math from within Python.
### Math
Python supports these mathematics operators:

* `+` - addition `2 + 2`
* `-` - subtraction `4 - 2` or negation `-2`
* `*` - multiplication `2 * 2`
* `/` - children's division (rounds every number down) `5 / 3`
* `%` - remainder or, as the cool kids call it, modulus `5 % 3`
* `**` - exponent 2 ** 3

You can use Python as a rudimentary calculator using just these operators.

We can also create variables in Python to store values.

Try typing in `x = 2` and then typing in `print x`

You should recieve `2`

`print` is a Python statement which outputs your data to what's known as `standard output` (aka `stdin`), `standard out`, or `stdout`. `print` is very valuable for seeing data that you've generated or for checking the value of a variable when debugging.

### Variables and Assignment
Here we also introduce the idea of assignment.

We are assigning the variable `x` the value of `2` by using the equals sign or assignment operator (`=`). In reality, Python's variables are more like names for data but that's a discussion for later.

Now that we've assigned `x` the value of `2` we can perform operations on `x` as if it was `2`. That means instead of `2 + 2` you can type in `x + 2` and you will recieve back `4`.

We can also chain all these operators to do slightly more complex mathematics. `x = 2 + 3 * 6`. This expression evaluates out the value of `20` and stores it in `x`. Order of operations (PEMDAS) applies. We can be more explicit about the order and say `x = 2 + (3 * 6)`.

And also if we wanted to do operations with x but not have to type it out twice (like this: `x = x + 2`) we can use a short cut by typing `x += 2`. This same shortcut can be done with all the other mathematics operators we've discussed.

# Beyond Math
## Strings
In addittion to math, Python also has what are known as strings. Strings are letters, words, sentences, paragraphs, or even essays. Anything that is based off of a letter is a string.

For example,
```python
x = "string"
```
stores the value "string" in x.

As you've probably guessed, Python has an understand of what kind of data it is working with at a given time. This is known as it's typing system. Each type has it's own special properties and rules about how it can be mixed with other types. It's somewhat similar to how Pokemon and their moves have types.

For example, you can add two integers by doing `2 + 2` and you will recieve 4. But adding two strings `"2"+"2"` will give you `"22"`. The addittion operator combined or, as the cool kids call it, concatenated the strings together since adding strings together mathematically doesn't make sense.

Then the question would be, how do strings and integers interact?

Try `2 + "2"`

You should recieve something discussing a `TypeError`. This is because the string type and the integer type cannot be added together. It doesn't even make sense.

Instead we can perform what's known as a cast and convert the type of one of the operands. We can use `int()` to convert the `"2" to 2` which is not a string and will be added together to get `4`.

> #### int(x=0)
> Convert a number or string x to an integer, or return 0 if no arguments are given. If x is a number, it can be a plain integer, a long integer, or a floating point number.


Or we can cast the integer to a string with `str()` which converts `2` to `"2"` which will be concatenated to create `"22"`.

> #### str(object="")
> Return a string containing a nicely printable representation of an object.

In the above example we introduce the int() and str() built-in functions. These functions are bundled into Python and are there for your use.


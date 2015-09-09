from os import path
del __builtins__.__dict__['__import__']
del __builtins__.__dict__['reload']

print "Welcome to the food menu!"
choices = (
    ("Chicken Asada Burrito", 7.69, "caburrito.txt"),
    ("Beef Chow Mein", 6.69, "beefchow.txt"),
    ("MeatBurger Deluxe", 10.49, "no description"),
    # ...
)

def print_description(n):
    print ""
    if n >= len(choices):
        print "No such item!"
    elif not path.exists(choices[n][2]):
        print "No description yet, but we promise it's tasty!"
    else:
        print open(choices[n][2]).read()

def show_menu():
    for i in xrange(len(choices)):
        print "[% 2d] $% 3.2f %s" % (i, choices[i][1], choices[i][0])

while True:
    print "Which description do you want to read?"
    show_menu()
    print_description(input('> '))
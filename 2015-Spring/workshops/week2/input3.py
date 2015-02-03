from random import randint

def printpegs(code):
    print " --------------------- "
    print " |",
    for c in code:
        print c, "|",
    print ""
    print " --------------------- "

print "Master Mind Game"

flag = "this_is_a_flag"

mm_code = (randint(0,9), randint(0,9), randint(0,9), randint(0,9), randint(0,9))
print "I've set my code. Guess it!"

print "Rules: You should input your guesses as 5 digits separated by commas."
print "       I will respond by marking the correct digits with a 2, marking"
print "       digits in the wrong place with a 1, and marking wrong digits 0."

while True:
    guess = str(input('guess> '))
    if len(guess) != 5:
        print "You must guess a 5-digit code!"
        continue

    printpegs(guess)

    right = map(lambda x,y: (x == y) + (x in mm_code), guess, mm_code)
    printpegs(right)

    if guess == mm_code:
        print "You got it right!"
        exit(0)

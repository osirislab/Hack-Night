print "Welcome to mystery math!"

flag = "xxxxxxxxxx"

while True:
    x = input("Enter number 1> ")
    x = x*x + ord(flag[0]) * ord(flag[1]) + ord(flag[2]) * x
    y = input("Enter number 2> ")
    if y / 6 + 7 - y == x:
        print "Here ya go! ", flag
        exit(0)
    else:
        print "Your lucky number is ", x - y

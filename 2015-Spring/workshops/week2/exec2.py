banned = [
    "import",
    "exec",
    "eval",
    "pickle",
    "os",
    "subprocess",
    "kevin sucks",
    "sys"
]

while True:
    data = raw_input(">>> ")

    for no in banned:
        if no.lower() in data.lower():
            print "No bueno"
            break
    else: # this means nobreak
        exec data

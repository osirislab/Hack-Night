#!/usr/bin/python3
import sys

if sys.version_info[0] < 3:
    input = raw_input

from login import LoginService

ls = LoginService()
user = None


def login_prompt():
    global user, ls
    print("Please log in")

    while True:
        uname = input("Username: ")
        if uname not in ls.users:
            print("User doesn't exist")
            return

        pw = input("Password: ")

        user = ls.check_login(uname, pw)
        if user:
            print("Logged in as %s" % (uname))
            return
        else:
            print("Invalid password")


def register():
    global ls, user
    uname = input("Username: ")
    if uname in ls.users:
        print("User already exists")
        return
    pw = input("Password: ")

    ls.register(uname, pw)
    user = ls.users[uname]


def logout():
    print("You can't log out")


def print_accounts(target):
    print("%s has %s on hand" % (target.uname, target.balance))
    if not target.accounts:
        print("You have no accounts")
    for account in range(len(target.accounts)):
        print("%d: %s" % (account, target.accounts[account]))


def transfer():
    global ls, user
    print_accounts(user)
    account_id = input("Select your account: ")
    if account_id.isdigit():
        account_id = int(account_id)
    else:
        print("Invalid account ID")
        return

    account = user.get_account(account_id)

    amount = input("Enter your amount: ")
    if amount.isdigit():
        amount = int(amount)
    else:
        print("Invalid amount")
        return

    target_name = input("Enter the recipient's username: ")
    if not target_name in ls.users:
        print("User doesn't exist")
        return

    target = ls.users[target_name]
    print_accounts(target)
    target_id = input("Enter the account ID to send to: ")
    if target_id.isdigit():
        target_id = int(target_id)
    else:
        print("Invalid account ID")
        return

    target_acc = target.get_account(target_id)

    if account.transfer(amount, target_acc):
        print("Transfer successful")
    else:
        print("Transfer failed")


def new_account():
    global user
    name = input("Account name: ")
    deposit = 0
    if user.balance > 0:
        print("You have %s on hand, how much do you want to deposit?" % (user.balance))
        deposit = input(">")
        if deposit.isdigit():
            deposit = int(deposit)
        else:
            print("Invalid deposit")
            return

    if user.make_account(name, deposit):
        print("Account created successfully")
    else:
        print("Account creation failed")


def close():
    global ls, user
    print_accounts(user)
    account_id = input("Select your account: ")
    if account_id.isdigit():
        account_id = int(account_id)
    else:
        print("Invalid account ID")
        return

    account = user.close_account(account_id)
    leftover = account.balance
    user.balance += leftover


account_routes = {
    "info": lambda: print_accounts(user),
    "exit": None,
    "transfer": transfer,
    "create": new_account,
    "close": close,
    "help": lambda: help_func(account_routes),
}


def accounts():
    if user is None:
        print("You aren't logged in")
        return

    help_func(account_routes)
    while True:
        route = input("accounts> ")
        if route == "exit":
            return

        if route in account_routes:
            account_routes[route]()
        else:
            print("Invalid route %s" % (route))


def help_func(routes):
    print("Commands: ")
    for route in routes:
        print("- %s" % (route))


with open("flag.txt", "r") as FILE:
    FLAG = FILE.read()


def flag():
    if user is None:
        print("You aren't logged in")

    if user.calculate_total() > 100:
        print(FLAG)
    else:
        print("You can't afford the flag")


routes = {
    "login": login_prompt,
    "register": register,
    "logout": logout,
    "accounts": accounts,
    "flag": flag,
    "help": lambda: help_func(routes),
}


def main():
    while True:
        help_func(routes)
        route = input("> ")
        if route in routes:
            routes[route]()
        else:
            print("Invalid route %s" % (route))


if __name__ == "__main__":
    main()

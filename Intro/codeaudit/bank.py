class Account(object):
    def __init__(self, name, balance=10):
        self.name = name
        self.balance = balance

    def transfer(self, amount, other):
        if self.balance >= amount:
            other.balance += amount
            self.balance -= amount
            return True
        return False

    def __str__(self):
        return "[ Account %s: $%d ]" % (self.name, self.balance)


class User(object):
    def __init__(self, uname, passwd):
        self.uname = uname
        self.passwd = passwd
        self.accounts = []
        self.balance = 10

    def make_account(self, name, start_value):
        new_account = None
        if self.balance >= start_value:
            new_account = Account(name, start_value)
            self.accounts.append(new_account)
            self.balance -= start_value
        return new_account

    def close_account(self, account_id):
        acc = self.get_account(account_id)
        self.accounts.pop(account_id)
        return acc

    def get_account(self, account_id):
        return self.accounts[account_id]

    def calculate_total(self):
        n = 0
        for acc in self.accounts:
            n += acc.balance
        return n

    def transfer(self, amount, other):
        if self.balance >= amount:
            other.balance += amount
            self.balance -= amount
            return True
        return False

from bank import *


def strcmp(s1, s2):
    """ thonk """
    l_s1 = len(s1)
    l_s2 = len(s2)
    if l_s1 != l_s2:
        return False

    for i in range(l_s1):
        if s1[i] != s2[i]:
            return False
    return True


class LoginService(object):
    users = {}
    banned_users = {}

    def __init__(self):
        pass

    def register(self, uname, passwd):
        if uname not in self.users:
            self.users[uname] = User(uname, passwd)

    def check_login(self, uname, passwd):
        if uname in self.banned_users:
            return None

        elif not strcmp(self.users[uname].passwd, passwd):
            return None
        return self.users[uname]

    def ban(self, uname):
        usr = self.users[uname]
        banned_users[uname] = usr

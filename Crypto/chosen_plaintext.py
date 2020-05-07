#!/usr/bin/env python2.7
"""
chosen_plaintext.py

    Demonstrates a challenge that involves encrypting blocks of information
    using ECB, where the user has some level of control of the input, and sensitive
    information exists within the blocks.
"""

import os
import sys

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

KEY = os.urandom(16)
FLAG = "flag{ecb_1s_b4d}"

def simple_pad(query):
    query = query + 'A'
    while len(query) % 16 != 0:
        query = query + 'A'
    return query


def encrypt(query):
    query = query + FLAG
    cipher = Cipher(algorithms.AES(KEY), modes.ECB(), backend=default_backend())
    aes_encrypt = cipher.encryptor()

    ct = aes_encrypt.update(simple_pad(query)) + aes_encrypt.finalize()
    return ct.encode("hex")


def construct_query(first, last, age):
    query = "query:"
    query += str(int(age) * "0")
    query += first + last
    return encrypt(query)


def parse(ciphertext):
    return [
        ciphertext[0:32], ciphertext[32:64],
        ciphertext[64:96], ciphertext[96:128]
    ]


def solve():
    flag = ""

    # server prepends 6 bytes of padding, so we add ten '0's to hit block boundary,
    # and a full block of 'A's to represent first + last name
    #
    #   First Name: AAAAA
    #   Last Name: AAAAA
    #   Age: 10
    cp = bytearray("query:0000000000" + "AAAAAAAAAAAAAAAA")

    insert_point = 16
    for i in range(0, 64):

        cp.insert(insert_point, '?')

        # iterate over characters
        for b in range(0x20, 0x7E):
            cp[insert_point] = chr(b)

            blocks = parse(encrypt(str(cp)))
            print("{} <> {}".format(blocks[1], blocks[3]))

            # [query:0000000000] [AAAAAAAAAAAAAAAA] [flag{ecb_1s_b4d}] []
            # [query:0000000000] [?AAAAAAAAAAAAAAA] [Aflag{ecb_1s_b4d] [}]
            # [query:0000000000] [??AAAAAAAAAAAAAA] [AAflag{ecb_1s_b4] [d}]
            # [query:0000000000] [???AAAAAAAAAAAAA] [AAAflag{ecb_1s_b] [4d}]

            # check if the third block matches up with the first input block we control
            if blocks[1] == blocks[3]:
                flag = chr(b) + flag
                break

    print("\n{}".format(flag))


def main():
    if len(sys.argv) == 2:
        if sys.argv[1] == "solve_me":
            return solve()

    first = raw_input("First Name: ")
    last = raw_input("Last Name: ")
    age = raw_input("Age: ")
    print("\n{}".format(construct_query(first, last, age)))


if __name__ == "__main__":
    main()

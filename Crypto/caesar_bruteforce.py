#!/usr/bin/env python3
"""
caesar_bruteforce.py

    Permutes shifts through every character of alphabet
    against input message characters.
"""

import sys

LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

if __name__ == "__main__":

    # take an encrypted input message
    message = sys.argv[1]

    for key in range(len(LETTERS)):
        translated = ""
        for symbol in message:

            # offset every letter in message by every letter in alphabet
            if symbol in LETTERS:

                # get number position of symbol
                num = LETTERS.find(symbol)
                num = num - key
                if num < 0:
                    num = num + len(LETTERS)

                translated = translated + LETTERS[num]
            else:
                translated = translated + symbol

        print("Key {} {}".format(key, translated))

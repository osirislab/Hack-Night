#!/usr/bin/env python3
"""
xor_bruteforce.py

    Performs a bruteforce attack against a single-byte XOR cipher,
    and also performs character frequency analysis in order to aggregate
    a frequency score.
"""

import sys

def get_english_score(input_bytes):
    character_frequencies = {
        'a': .08167, 'b': .01492, 'c': .02782, 'd': .04253,
        'e': .12702, 'f': .02228, 'g': .02015, 'h': .06094,
        'i': .06094, 'j': .00153, 'k': .00772, 'l': .04025,
        'm': .02406, 'n': .06749, 'o': .07507, 'p': .01929,
        'q': .00095, 'r': .05987, 's': .06327, 't': .09056,
        'u': .02758, 'v': .00978, 'w': .02360, 'x': .00150,
        'y': .01974, 'z': .00074, ' ': .13000
    }
    return sum([character_frequencies.get(chr(byte), 0) for byte in input_bytes.lower()])


def single_char_xor(input_bytes, char_value):
    """Returns the result of each byte being XOR'd with a single value.
    """
    output_bytes = b''
    for byte in input_bytes:
        output_bytes += bytes([byte ^ char_value])
    return output_bytes


def main():
    hexstring = sys.argv[1]

    ciphertext = bytes.fromhex(hexstring)
    potential_messages = []
    for key_value in range(256):
        message = single_char_xor(ciphertext, key_value)
        score = get_english_score(message)
        data = {
            'message': message,
            'score': score,
            'key': chr(key_value)
            }
        potential_messages.append(data)
    best_score = sorted(potential_messages, key=lambda x: x['score'], reverse=True)[0]
    for item in best_score:
        print("{}: {}".format(item.title(), best_score[item]))

if __name__ == '__main__':
    main()

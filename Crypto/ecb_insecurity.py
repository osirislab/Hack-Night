#!/usr/bin/env python
import os
import binascii

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

BLOCKLEN = 16

def blocks(data):
    split = [binascii.hexlify(data[i:i+BLOCKLEN]) for i in range(0, len(data), BLOCKLEN)]
    return ' '.join(split)


if __name__ == "__main__":

    # initialize a random key
    k = os.urandom(16)
    print 'k = %s' % binascii.hexlify(k)

    # create an instance of AES-128 to encrypt and decrypt
    cipher = Cipher(algorithms.AES(k), modes.ECB(), backend=default_backend())
    aes_encrypt = cipher.encryptor()

    # repeating inputs
    p = '\x12' * BLOCKLEN *2

    # encrypt plaintext p to ciphertext c
    c = aes_encrypt.update(p) + aes_encrypt.finalize()
    print 'enc(%s) = %s' % (blocks(p), blocks(c))

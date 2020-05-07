#!/usr/bin/env python2.7
"""
aead.py

    Simple example of AEAD with ChaCha20Poly1305

"""
import os
from cryptography.hazmat.primitives.ciphers.aead import ChaCha20Poly1305

data = b"a secret message"
aad = b"authenticated but unencrypted data"

# generate a random key and object instance
key = ChaCha20Poly1305.generate_key()
chacha = ChaCha20Poly1305(key)

# create a random nonce
nonce = os.urandom(12)
ct = chacha.encrypt(nonce, data, aad)

print(chacha.decrypt(nonce, ct, aad))

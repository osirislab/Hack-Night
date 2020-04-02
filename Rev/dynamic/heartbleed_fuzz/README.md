# OpenSSL Heartbleed Fuzz Example

We use this to examine and find a real-world vulnerability, CVE-2014-0160, aka Heartbleed, in OpenSSL. This was a prominent attack, but the actual root cause analysis shows how rudimentary the actual bug was (lack of a bounds check on dynamically allocated memory == OOB read).

# Setup

The build setup is replicated from [afl-training](https://github.com/mykter/afl-training), which is really nice for rapidly getting an environment setup to perform fuzzing on some targets.

Inside the vulnerable OpenSSL source:

```
$ CC=afl-clang CXX=afl-clang++ ./config
$ AFL_USE_ASAN=1 make
```

Building the target:

```
$ AFL_USE_ASAN=1 afl-clang-fast++ -g harness.cpp openssl/libssl.a openssl/libcrypto.a -o harness -I openssl/include -ldl
```

Running the fuzzer:

```
mkdir in/
cat "AAAAAAAAAA" >> in/1
afl-fuzz -i in -o out -m none ./harness
```

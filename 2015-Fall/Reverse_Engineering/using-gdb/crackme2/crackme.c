#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned u_int;

u_int do_hash_thing(unsigned char *str) {
    u_int i, hash, len, tmp, shift;

    hash = 0xcafebabe;
    len = strlen((char *) str);
    len = len > 32 ? 32 : len;

    for (i = 0; i < len; i++) {
        shift = (i % 4) * sizeof(u_int) * 2;
        printf("[DEBUG] %d\n", shift);
        tmp = str[i] << shift;
        hash ^= tmp;
        printf("[DEBUG] 0x%08x\n", hash);
    }

    return hash;
}

int main()
{
    char input[256];

    printf("Can you crack me?: ");
    fgets(input, 256, stdin);

    if (do_hash_thing((unsigned char *) input) == 0xdeadbeef) {
        printf("You good brah\n");
    }
    else {
        printf("Check yo self\n");
    }
}

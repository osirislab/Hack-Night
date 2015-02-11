#include <unistd.h>

int do_the_thing(char *userstring) {
    
    char buf[128];
    char *src, *dst;
    src = userstring;
    dst = buf;
    // brah, do you even code?
    while(*src != 0x0) {
        *dst++ = *src++;
    }

    return 0;
}

int main() {
    // Make a character array with 2048 slots for characters
    // aka, make a string with length of 2048
    char userstring[2048];
    
    // Read from standard in until when? (hint `man read` or look online for
    // C documentation)
    // (0 means standard in)
    read(0, userstring, sizeof(userstring));
    
    do_the_thing(userstring);

    return 0;
}

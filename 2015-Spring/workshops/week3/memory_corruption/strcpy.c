#include <unistd.h>
#include <string.h>
#include <stdio.h>

int call_strcpy(char* userstring)
{
    char buf[128];

    // make copy of data to manipulate
    // (if you are unsure of what strcpy does, type `man strcpy`)
    strcpy(buf, userstring);

    // print our newly copied string
    printf("%s", buf);

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

    call_strcpy(userstring);

    return 0;
}

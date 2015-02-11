#include <unistd.h>
#include <string.h>

int call_strncat(char *string) {
    char buf1[256]; // same size as string so it is all good...right?
    char* lol_im_a_string = "some string here";

    strncat(buf1, lol_im_a_string, sizeof(buf1)-1);
    /* ... */
    strncat(buf1, string, sizeof(buf1)-1);

    return 0;
}

int main() {
    char userstring[256];

    read(0, userstring, sizeof(userstring));

    call_strncat(userstring);

    return 0;
}


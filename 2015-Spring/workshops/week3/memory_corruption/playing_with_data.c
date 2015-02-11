#include <unistd.h>
#include <stdio.h>
#include <string.h>

struct mystruc
{
    int a;
    char b;
    float c;
};

char imaCharArray[] = "Hello, I am a string";

int main(int argc, char** argv)
{
    struct mystruc structVar = {5,'a',3.9};
    struct mystruc* strucPtr = &structVar;

    unsigned char* charPtr = (unsigned char*) strucPtr;
    int i;

    printf("structure size : %zu bytes\n", sizeof(struct mystruc));

    for(i=0; i < sizeof(struct mystruc); i++)
        printf("%02x ", charPtr[i]);

    return 0;
}

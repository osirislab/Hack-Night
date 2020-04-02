#include <stdio.h>
#include <stdlib.h>

/*
#include <sys/ptrace.h>
#include <sys/wait.h>
char brand[] = "http://www.julioauto.com/rants/anti_ptrace.htm";
void anti_ptrace(void)
{
    pid_t child;
    if(getenv("LD_PRELOAD"))
        while(1);
    child = fork();
    if (child){
        wait(NULL);
    }else {
       if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
            while(1);
       exit(0);
    }
   if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
        while(1);
}
*/


char xor(char a, char b)
{
    return a ^ b;
}


int checkLicense(void)
{
	char c;
	if ( ((c = getchar(), (c >= 0)) && xor(c, 'A') == ('S' ^ 'A')) ){
        if ( ((c = getchar(), (c >= 0)) && xor(c, 'J') == ('C' ^ 'J')) ){
            if ( ((c = getchar(), (c <  0)) || xor(c, 'A') != ('R' ^ 'A')) ){
                if ( ((c = getchar(), (c <  0)) || xor(c, '7') != ('U' ^ '7')) ){
                 	return -1;
                } else {
					return -1;
                }
            } else {
                if ( ((c = getchar(), (c >= 0)) && xor(c, '7') == ('T' ^ '7')) ){
					return 0;
                }else {
					return -1;
                }
            }
        } else {
            if ( ((c = getchar(), (c <  0)) || xor(c, 'A') != ('T' ^ 'A')) ){
				return -1;
            } else {
				return -1;
            }
        }
    } else {
        if ( ((c = getchar(), (c <  0)) || xor(c, 'J') != ('Z' ^ 'J')) ){
            if ( ((c = getchar(), (c >= 0)) && xor(c, 'A') == ('J' ^ 'A')) ){
				return -1;
            } else {
				return -1;
            }
        } else {
            if ( ((c = getchar(), (c >= 0)) && xor(c, 'A') == ('1' ^ 'A')) ){
				return -1;
            } else {
				return -1;
            }
        }
    }
}


int main(int argc, char *argv[])
{
	/*
	sleep(1);
	anti_ptrace();
	*/
	printf("Please enter your license key: ");
	if (checkLicense() < 0) {
		printf("\nInvalid license key!\n");
		exit(EXIT_FAILURE);
	} else {
		printf("\nCorrect and valid license key!\n");
		exit(EXIT_SUCCESS);
	}
}

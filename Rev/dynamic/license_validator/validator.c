#include <stdio.h>
#include <stdlib.h>

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
	printf("Please enter your license key: ");
	if (checkLicense() < 0) {
		printf("\nInvalid license key!\n");
		exit(EXIT_FAILURE);
	} else {
		printf("\nCorrect and valid license key!\n");
		exit(EXIT_SUCCESS);
	}
}

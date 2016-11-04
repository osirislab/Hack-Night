#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void explode() {
  printf("\n"
           "     _.-^^---....,,--      \n"
           " _--                  --_  \n"
           "<                        >)\n"
           "|         B O O M         |\n"
           " \\._                   _./ \n"
           "    ```--. . , ; .--'''    \n"
           "          | |   |          \n"
           "       .-=||  | |=-.       \n"
           "       `-=#$%%&%%$#=-'       \n"
           "          | ;  :|          \n"
           " _____.,-#%%&$@%%#&#~,._____ \n");
  exit(0);
}

int prime(int n) {
  if (n < 3) return 1;
  else {
    for (int i=2; i < sqrt(n); ++i)
      if (n % i == 0) return 0;
  }
  return 1;
}

void round1() {
  int x;
  printf("Round 1: ");
  scanf("%d%*c", &x);
  if (prime(x) == 0) explode();
  printf("You got lucky this time.\n");
}

void round2() {
  char pass[256];
  
  printf("Round 2: ");
  fgets(pass, sizeof(pass), stdin);

  if (strlen(pass)-1 != 3) explode();
  if (pass[0] != pass[2]) explode();
  
  printf("Not bad\n");
}

void round3() {
  char pass[256];
  
  printf("Round 3: ");
  fgets(pass, sizeof(pass), stdin);
  
  if (strlen(pass)-1 != 6) explode();
  if (pass[0] != 'o') explode();
  if (pass[1] != 's') explode();
  if (pass[2] != 'i') explode();
  if (pass[3] != 'r') explode();
  if (pass[4] != 'i') explode();
  if (pass[5] != 's') explode();
  
  printf("Almost there\n");
}

void round4() {
  char pass[256];
  size_t n = 0;
  
  printf("Round 4: ");
  fgets(pass, sizeof(pass), stdin);
  
  if (strlen(pass)-1 != 8) explode();
  if (pass[n++] != 100) explode();
  if (pass[n] != pass[n-1]+1) explode();
  n++;
  if (pass[n] != pass[n-1]-4) explode();
  n++;
  if (pass[n] != pass[n-1]+3) explode();
  n++;
  if (pass[n] != pass[n-1]-2) explode();
  n++;
  if (pass[n] != pass[n-1]+3) explode();
  n++;
  if (pass[n] != pass[n-1]) explode();
  n++;
  if (pass[n] != pass[n-1]+1) explode();
  
  printf("Woah, didn't think you'd get this far\n");
}


int main() {
  char flag[256];
  FILE* f;

  printf("So I hear you're looking for a flag. First, you must defuse my bomb.\n");
  
  round1();
  round2();
  round3();
  round4();

  printf("I guess you can have the flag\n");
  
  f = fopen("flag.txt","r");
  if (f == NULL) {
    perror("Error opening file\n");
  }
  else {
    if (fgets(flag, sizeof(flag), f) != NULL) {
      puts(flag);
      fclose(f);
    }
  }

}



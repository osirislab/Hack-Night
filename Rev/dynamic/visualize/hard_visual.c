#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void win(){
  puts("yaaaay you win!!!\n");
  exit(0);
}

void lose(){
  puts("You do not win : /");
  exit(0);
}

int32_t get_number() {
  char buf[0x80];
  fgets(buf, sizeof(buf), stdin);
  return strtol(buf, NULL, 10);
}

void main(){
  int score = 1337;
  int32_t input = get_number();
  input += 69;
  input -= 420;
  input -= 1;
  input += 123;
  input -= 420;
  input += 420;
  input -= 7;
  input -= 1337;
  input += 5;
  input -= 8;
  input += 69;
  if (input == score) {
    win();
  } else {
    lose();
  }
}

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
  int32_t score = 1337;
  int32_t input = get_number();
  if (input > score){
    win();
  } else {
    lose();
  }
}

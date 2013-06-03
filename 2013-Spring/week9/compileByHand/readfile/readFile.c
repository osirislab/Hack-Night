#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024


void printInts(int * buffer, int number){
  for(int i=0; i<number; i+=2){
    printf("%d, %d\n",buffer[i],buffer[i+1]);
  }
  return;
}

int readInts(FILE* file, int* buffer){
  int ret;
  ret = fread(buffer, sizeof(int), BUFSIZE, file);
  return ret;
}

int main(int argc,char** argv){
  int buffer[BUFSIZE];
  char * filename = "points";
  FILE* file = fopen(filename,"r");
  int numInts;
  numInts = readInts(file,buffer);
  printInts(buffer, numInts);
  return 0;
}

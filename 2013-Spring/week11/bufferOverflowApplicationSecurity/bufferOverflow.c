#include <stdio.h>

#define READSIZE 0x1000

void countLines(FILE* f){
  char buf[0x400];//should be big enough for anybody
  int lines=0;
  fread(buf,READSIZE,1,f);  
  
  for(int i=0;i<0x400;i++)
    if(buf[i] == '\n')
      lines++;
    
  
  printf("The number of lines in the file is %d\n",lines);
  return;
}

int main(int argc,char** argv){
  if(argc<2){
    printf("Proper usage is %s <filename>\n",argv[0]);
    exit(0);
  }
  FILE* myfile=fopen(argv[1],"r"); 
  countLines(myfile);
  return 0;
}

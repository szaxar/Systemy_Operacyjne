#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RECORD_SIZE 1024

int size(int x){

int tmp=0;
while(x>0){
x=x/10;
tmp++;
}
return tmp;
}

int main(int argc, char ** argv) {
  srand(time(NULL)); 

  FILE * file = fopen("aaaa.txt", "w");

  for (int i=1; i<100; i++) {
    fprintf(file, "%d", i);
   
    for (int j=0; j<RECORD_SIZE-size(j);j++) {
      fprintf(file, "%c", 'A' + (int)(random() % 26));
    }
  }

  fclose(file);
  return 0;
}

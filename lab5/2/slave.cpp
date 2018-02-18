#include <iostream>
#include<stdlib.h>
#include <stdio.h>     
#include <complex.h> 
#include <math.h>
#include<string.h>

#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

#include <unistd.h>

using namespace std;
int D_X_MIN = -2;
int D_X_MAX = 1;
int D_Y_MIN = -1;
int D_Y_MAX = 1;

double complex generate(){
  double x = (double)rand()/RAND_MAX *(D_X_MAX - D_X_MIN) + D_X_MIN;
  double y = (double)rand()/RAND_MAX *(D_Y_MAX - D_Y_MIN) + D_Y_MIN;
  return x + y *I;
}


int main(int argc, char ** argv){

char *path=argv[1];
int  N =atoi(argv[2]);
int K=atoi(argv[3]);

int fd= open(path,O_WRONLY);
if(fd<0) {
cout<<"blad potoku"<<endl;
return -1;
}
cout<<"otwarto potok mam sie wykonac"<<N<<endl;
for(int i=0;i<N;i++){
double complex c=generate();
double complex tmp=c;
int tmp2=0;
while(cabs(tmp)<=2 || tmp2==K){ /// |tmp|<=2
tmp2++;
tmp=tmp*tmp+c;
}
char buffer[100];
 sprintf(buffer, "%.3f %.3f %d\n", creal(c), cimag(c), tmp2);  
write(fd, buffer, strlen(buffer));
cout<<"Wysłałem "<<buffer<<" "<<i<<"raz"<<endl;
}
cout<<"Wykonalem sie"<<endl;
close(fd);
return 0;
}

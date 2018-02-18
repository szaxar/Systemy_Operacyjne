
#include<stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int P;
int D_X_MIN = -2;
int D_X_MAX = 1;
int D_Y_MIN = -1;
int D_Y_MAX = 1;

void scale_complex(double *re, double *im) {
    *re = P * fabs(-2 - *re) / 3.0;  /// 600 * |-2 - re) /3
    *im = P * fabs(1 - *im) / 2.0;
}

void write_graph(int **T) {
printf("Rysuje");
    FILE* file = fopen("data","w");
    if(!file) {
        perror("Error creating the data file\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<P;++i) {
        for(int j=0;j<P;++j) {
            fprintf(file,"%d %d %d\n",i,j,T[i][j]);
        }
    }
    fclose(file);

    FILE* gnuplot = popen("gnuplot","w");
    fprintf(gnuplot,"set view map\n");
    fprintf(gnuplot, "set xrange [0:%d]\n",P-1);
    fprintf(gnuplot, "set yrange [0:%d]\n",P-1);
    fprintf(gnuplot, "plot 'data' with image\n");

    fflush(gnuplot);

    fprintf(stdout, "Waiting for char to exit...\n");
    getc(stdin);

    pclose(gnuplot);
}

int main(int argc, char ** argv){

double re, im;
 int iters;
char *path=argv[1];
P =atoi(argv[2]);


int **tab = malloc(sizeof(int*)*P);
  for(int i=0;i<P;++i) {
      tab[i] = calloc((size_t)P,sizeof(int));
}


for(int i=0;i<P;i++){
   for(int j=0;j<P;j++){
tab[i][j]=0;
	}
}

mkfifo(path,0666);
int fd= open(path,O_RDONLY);

char buffer[100];
    while(read(fd, buffer, 100)>0){
     sscanf(buffer,"%lf %lf %d",&re,&im,&iters); //wczytaj
	printf("%lf %lf %d",re,im,iters);
     scale_complex(&re,&im);  /// scal do rozmiaru tablicy
      tab[(int)re][(int)im] = iters; /// 
}
printf("zamykam");
close(fd); 
 unlink(path);
write_graph(tab);

for(int i=0;i<P;++i) {
       free(tab[i]);
   }
free(tab);

return 0;
}

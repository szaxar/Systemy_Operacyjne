#include <stdlib.h>
#include <pthread.h>
#include<stdio.h>
#include<string.h>
#include <semaphore.h>
#include <unistd.h>

int P;
int N;
pthread_t * threads1;
pthread_t * threads2;
//czytelnciy
int _div;
int tab[100];
int flaga;
int readers=0;
int writterswaiting=0;
int writters=0;
int counter=0;
sem_t reader;
sem_t writer;

	void * readLine(void * arg) {
while(1){
counter=0;
sem_wait(&reader);
readers++;
if(readers==1) sem_wait(&writer);
 sem_post(&reader);


for(int i=0;i<100;i++){
if(tab[i]%_div==0) {
printf("Znalazlem wartosc %d o indeksie %d\n",tab[i],i);
counter++;
}
}
printf("Znalazlem %d wartosc \n",counter);
sem_wait(&reader);
readers--;
if(readers==0) sem_post(&writer);
sem_post(&reader);
sleep(4);
}
return NULL;
}

	void * writeLine(void * arg) {
while(1){
sem_wait(&writer);
int x=rand()%50+1;
for(int i=0;i<x;i++){
int y=rand()%10;
int z=rand()%100;
tab[z]=y;
 printf("Zmodyfikowalem indeks %d o wartosci %d\n",y,z);
}
 sem_post(&writer);
sleep(4);
}
return NULL;
}

	int main(int argc, char ** argv){
   N=atoi(argv[1]);
   P=atoi(argv[2]);
   _div=atoi(argv[3]);

if(strcmp(argv[4], "-i") && argv[4]!=NULL) flaga=0;
else flaga=1;

for(int i=0;i<100;i++){
tab[i]=-1;
}
sem_init(&reader, 0, 1);
sem_init(&writer, 0, 1);

threads1= calloc(N,sizeof(pthread_t));
threads2= calloc(P,sizeof(pthread_t));

for(int i = 0;i < N; i++)   pthread_create(&threads1[i], NULL, readLine, NULL);
for(int i = 0;i < P; i++) pthread_create(&threads2[i], NULL, writeLine, NULL);
for(int i = 0; i < P; i++) pthread_join(threads2[i], NULL);
for(int i = 0; i < N; i++) pthread_join(threads1[i], NULL);

free(threads1);
free(threads2);
sem_destroy(&reader);
sem_destroy(&writer);
    return(0);
}

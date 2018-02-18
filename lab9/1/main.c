#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>
#define _GNU_SOURCE
#include <sys/syscall.h>
///pisarze 
pthread_mutex_t mutex;
pthread_mutex_t mutex2;
int P;
int N;
pthread_t * threads1;
pthread_t * threads2;
pthread_mutexattr_t attr;
pthread_cond_t conditional = PTHREAD_COND_INITIALIZER;
int _div;
int tab[100];
int flaga;
int readers=0;
int writterswaiting=0;
int writters=0;
int counter=0;
	void * readLine(void * arg) {
  
while(1){
counter=0;
pthread_mutex_lock(&mutex);
while(writterswaiting){
            pthread_cond_wait(&conditional, &mutex);
}
readers++;
pthread_mutex_unlock(&mutex);

for(int i=0;i<100;i++){
if(tab[i]%_div==0) {
printf("Znalazlem wartosc %d o indeksie %d\n",tab[i],i);
counter++;
}
}
printf("Znalazlem %d wartosc \n",counter);
 pthread_mutex_lock(&mutex);
        readers--;
        pthread_cond_broadcast(&conditional); //wysyla do wszystkich oczekajacych 
pthread_mutex_unlock(&mutex);
sleep(4);
}
return NULL;
}


	
void * writeLine(void * arg) {
while(1){
pthread_mutex_lock(&mutex);
writterswaiting++;

while(readers || writters){
	pthread_cond_wait(&conditional, &mutex); // czeka
}
writters++;
int x=rand()%50+1;
for(int i=0;i<x;i++){
int y=rand()%10;
int z=rand()%100;
tab[z]=y;
 printf("Zmodyfikowalem indeks %d o wartosci %d\n",y,z);
}
        writters--;
        writterswaiting--;
        pthread_cond_broadcast(&conditional);
pthread_mutex_unlock(&mutex);
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

pthread_mutexattr_init(&attr);
pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

threads1= calloc(N,sizeof(pthread_t));
threads2= calloc(P,sizeof(pthread_t));

pthread_mutex_init(&mutex, &attr);
pthread_mutex_init(&mutex2, &attr);
pthread_mutex_lock(&mutex2);

for(int i = 0;i < N; i++)   pthread_create(&threads1[i], NULL, readLine, NULL);
for(int i = 0;i < P; i++) pthread_create(&threads2[i], NULL, writeLine, NULL);
 pthread_mutex_unlock(&mutex2);

for(int i = 0; i < N; i++) pthread_join(threads1[i], NULL);
for(int i = 0; i < P; i++) pthread_join(threads2[i], NULL);
free(threads1);
free(threads2);

pthread_mutex_destroy(&mutex);
pthread_mutex_destroy(&mutex2);
pthread_cond_destroy(&conditional);
    return(0);
}

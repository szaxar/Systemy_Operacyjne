 #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>
       #include <iostream>
       #include <string.h>
       #include <stdlib.h>
       #include<sys/shm.h>
       #include<sys/ipc.h>
       #include <stdio.h>
  	#include <unistd.h>
       #include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>
       using namespace std;

       typedef enum semType{
         BARBER = 0, FIFO = 1, CHECKER = 2
       } semType;

typedef struct timespec tp;

int semator_index;
const int N=10;
const int S=20;
int counter=0;
int seg;
int SID;
pid_t client_pid;

 struct Fifo{
  int max;
  int head;
  int tail;
  pid_t chair;
  pid_t tab[N];
};
Fifo *fifo;
////////////////////////
//obsluga kolejki
void InitFifo(){
  fifo->max = N;
  fifo->head = -1;
  fifo->tail = 0;
  fifo->chair = 0;
  for(int i=0;i<N;i++){
    fifo->tab[i]=0;
  }
}

int isEmptyFifo(Fifo* fifo){
  if(fifo->head == -1) return 1;
  else return 0;
}

int isFullFifo(Fifo* fifo){
  if(fifo->head == fifo->tail) return 1;
  else return 0;
}

pid_t popFifo(Fifo* fifo){
  if(isEmptyFifo(fifo) == 1) return -1;

  fifo->chair = fifo->tab[fifo->head++];
  if(fifo->head == fifo->max) fifo->head = 0;

  if(fifo->head == fifo->tail) fifo->head = -1;

  return fifo->chair;
}

int pushFifo(Fifo* fifo, pid_t x){
  if(isFullFifo(fifo) == 1) return -1;
  if(isEmptyFifo(fifo) == 1){
    fifo->head = fifo->tail;
  }

  fifo->tab[fifo->tail++] = x;
  if(fifo->tail == fifo->max) fifo->tail = 0;
  return 0;
}

///////////////////////////////////////////////


#define gettime() clock_gettime(CLOCK_MONOTONIC, &tp)

       int main(){
fifo=new Fifo();
        key_t klucz=ftok(getenv("HOME"),'p'); ///generuje klucz
printf("wygenerowano klucz %d\n",klucz);

seg=shmget(klucz,sizeof(Fifo),IPC_CREAT | 0600); //utworz segement pamiecie od klucza
 printf("Wygenerowano segement pamięci %d\n",seg);

void* adr=shmat(seg,0,0);
fifo = (Fifo*) adr; //rzutowania wskaznika
InitFifo();

     SID = semget(klucz,N+2, IPC_CREAT | IPC_EXCL | 0666);  ////utworz semafor
printf("Wygenerowano semafor %d\n",SID);
for(int i=1; i<N+2; i++){
    semctl(SID, i, SETVAL, 1); // Wszystkie na 1 oprocz serwera
  }
 semctl(SID, 0, SETVAL, 0); //serwer utorz 0

 struct sembuf sops;
 sops.sem_num = BARBER;
 sops.sem_op = -1;
 sops.sem_flg = 0;
int flaga=0;
while(1){

  if(isEmptyFifo(fifo)==1 && client_pid == -1){ //zasnij
    //printf("Oczekuje na klientow");
    sops.sem_num = BARBER;
    sops.sem_op = 0;
    sops.sem_flg = 0;
    semop(SID, &sops, 1);
  }
  semator_index=fifo->head;
client_pid = popFifo(fifo);

if(client_pid == -1){ //zwolnij miejsce
semctl(SID, BARBER, SETVAL, 1);
  flaga=1;
}
   if(flaga==0){
     /*
      gettime();
      printf("[%d---%7d] Zaczalem stzryzenie klienta %d.\n", (int) tp.tv_sec, (int) tp.tv_nsec, client_pid);
      semctl(SID, CHECKER + semator_index, SETVAL, 0);
      gettime();
      printf("[%d---%7d] Skonczylem strzyzenie klienta %d.\n", (int) tp.tv_sec, (int) tp.tv_nsec, client_pid);
*/
semctl(SID, CHECKER + semator_index, SETVAL, 0);
      semctl(SID, BARBER, SETVAL, 1);
  }



  }



       return 0;
       }

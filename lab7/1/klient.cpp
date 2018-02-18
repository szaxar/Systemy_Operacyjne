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

       using namespace std;
int krzeslo;
const int N=10;
const int S=20;
int counter=0;
int SID;
typedef enum semType{
         BARBER = 0, FIFO = 1, CHECKER = 2
       } semType;
struct timespec tp;

struct Fifo{
  int max;
  int head;
  int tail;
  pid_t chair;
  pid_t tab[10];
};
Fifo *fifo=NULL;
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
  return fifo->tail;
}
#define gettime() clock_gettime(CLOCK_MONOTONIC, &tp)
///////////////////////////////////////////////
void takeplace() {
  krzeslo = pushFifo(fifo, getpid());
  if (krzeslo != fifo->head)
    printf("%d [%d---%7d]    Zajalem miejsce w poczekalni\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
  else
    printf("%d [%d:%7d]    Jestem pierwszy w kolejce\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
}


void dzialanie_klienta() {
  gettime();
  if (isEmptyFifo(fifo) && semctl(SID,BARBER ,GETVAL, 0)) { // kolejka jest pusta i fryzjer nic nie robi
   takeplace();
   struct sembuf s = {BARBER, -1, IPC_NOWAIT};
     semop(SID, &s, 1);
     printf("%d [%d---%7d]  Fryzjer obudzony!\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
   ////
   struct sembuf x = {2 + krzeslo, 0, 0};
   semop(SID, &x, 1);
   gettime();
   counter++;
   semctl(SID, 2 + krzeslo, SETVAL, 1);
   printf("%d [%d---%7d] Zostalem ostrzyzony\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);

 } else if (semctl(SID,BARBER,GETVAL, 0)) {
    struct sembuf s = {BARBER, -1, 0};
    semop(SID, &s, 1);
  } else if (isFullFifo(fifo)) {
     printf("%d [%d---%7d]    Nie ma juz wolnych miejsc, opuszcam zaklad\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
  } else {
    takeplace();
    struct sembuf x = {2 + krzeslo, 0, 0};
    semop(SID, &x, 1);
    gettime();
    counter++;
    semctl(SID, 2 + krzeslo, SETVAL, 1);
    printf("%d [%d---%7d] Zostalem ostrzyzony\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
  }
}

#define gettime() clock_gettime(CLOCK_MONOTONIC, &tp)
       int main(){
        key_t klucz=ftok(getenv("HOME"),'p');
cout<<"wygenerowano klucz "<<klucz<<endl;
        int seg=shmget(klucz,sizeof(Fifo),IPC_CREAT | 0600); //utworz segement pamiecie od klucza
 cout<<"Wygenerowano segement pamięci "<<seg<<endl;


void* adr=shmat(seg,0,SHM_RND);
fifo = (Fifo*) adr;

   SID=semget(klucz,1,IPC_CREAT | 0600); /// utworz semafor
cout<<"Wygenerowano semafor "<<SID<<endl;


for(int i=0;i<5;i++){ //ilosc kilentow
  pid_t id = fork();
if(id==0){
while(counter<S){
dzialanie_klienta();
}
}
}
 cout<<"Wszyscy klienci zostal wyslani "<<endl;
  while(1){
    wait(NULL); // czekaj na dzieci
  }








       return 0;
       }

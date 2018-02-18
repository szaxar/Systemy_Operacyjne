 #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>
       #include <string.h>
       #include <stdlib.h>
       #include <stdio.h>
  	#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct timespec tp;

int semator_index;
int N=10;
const int S=20;
int counter=0;

typedef struct Fifo{
  int max;
  int head;
  int tail;
  pid_t chair;
  pid_t tab[10];
} Fifo;
struct Fifo *fifo;


void InitFifo(struct Fifo* fifo){
  fifo->max = N;
  fifo->head = -1;
  fifo->tail = 0;
  fifo->chair = 0;
  for(int i=0;i<N;i++){
    fifo->tab[i]=0;
  }
}

int isEmptyFifo(struct Fifo* fifo){
  if(fifo->head == -1) return 1;
  else return 0;
}

int isFullFifo(struct Fifo* fifo){
  if(fifo->head == fifo->tail) return 1;
  else return 0;
}

pid_t popFifo(struct Fifo* fifo){
  if(isEmptyFifo(fifo) == 1) return -1;

  fifo->chair = fifo->tab[fifo->head++];
  if(fifo->head == fifo->max) fifo->head = 0;

  if(fifo->head == fifo->tail) fifo->head = -1;

  return fifo->chair;
}


#define gettime() clock_gettime(CLOCK_MONOTONIC, &tp)

#define SEMNAME "sem8"
#define ACTIONSEM "action8"
#define SHMNAME "shm8"
#define NNAME "N8"
#define AMMOUNT 10
sem_t *semator_id, *semator_akcja;
int shmid, Nid;
Fifo* fifo;
int* adres;
sem_t** sems;
int x;

       int main(){

         semator_akcja = sem_open(ACTIONSEM, (O_RDWR | O_CREAT), 0644, 1);
         semator_id = sem_open(SEMNAME, (O_RDWR | O_CREAT), 0644, 0);
        sems = malloc(N * sizeof(sem_t*));

        char dane[AMMOUNT];
        for (int i=0; i<N; i++) {
          sprintf(dane, "/%d", i);
          sems[i] = sem_open(dane, (O_RDWR | O_CREAT), 0644, 0);
        }

        Nid = shm_open(NNAME, (O_RDWR | O_CREAT), 0644);
        ftruncate(Nid, sizeof(int));
        adres = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, Nid, 0);
        *adres = N;


        size_t rozmiar = sizeof(Fifo);
        shmid = shm_open(SHMNAME, (O_RDWR | O_CREAT), 0644);
        ftruncate(shmid, rozmiar);
         fifo= mmap(NULL, rozmiar, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
        InitFifo(fifo);


        while (1) {
          int flaga=0;

          sem_getvalue(semator_id, &x); //zasniecie
          if (x == 0)
            printf("Oczekuje na klientow\n");
          sem_wait(semator_id);

          int klient = fifo->head;
          pid_t pid = popFifo(fifo);
          if (pid == -1){
            flaga=1;
          }
          if(flaga ==0){
          printf("Ostrzyglem klienta %d\n", pid);
          sem_post(sems[klient]);
          printf("%d cut\n", pid);
        }
      }

      sem_close(semator_id);
      sem_unlink(SEMNAME);
      sem_close(semator_akcja);
      sem_unlink(ACTIONSEM);


      for (int i=0; i<N; i++) {
        sprintf(dane, "/%d", i);
        sem_close(sems[i]);
        sem_unlink(dane);
      }
      free(sems);

       return 0;
       }

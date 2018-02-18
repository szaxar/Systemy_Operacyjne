#include <sys/types.h>

      #include <stdlib.h>
      #include<sys/shm.h>
      #include<sys/ipc.h>
      #include <stdio.h>
   #include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

const int N=10;
const int S=5;
const int C=5;
int counter=0;
struct timespec tp;

typedef struct Fifo{
  int max;
  int head;
  int tail;
  pid_t tab[20];
}Fifo ;
Fifo *fifo;

int isEmptyFifo(struct Fifo* fifo){
  if(fifo->head == -1) return 1;
  else return 0;
}

int isFullFifo(struct Fifo* fifo){
  if(fifo->head == fifo->tail) return 1;
  else return 0;
}

int pushFifo(struct Fifo* fifo, pid_t x){
  if(isFullFifo(fifo) == 1) return -1;
  if(isEmptyFifo(fifo) == 1){
    fifo->head = fifo->tail;
  }

  fifo->tab[fifo->tail++] = x;
  if(fifo->tail == fifo->max) fifo->tail = 0;
  return fifo->tail;
}
#define gettime() clock_gettime(CLOCK_MONOTONIC, &tp)

sem_t *semator_id, *semator_akcja;
int shmid;
struct Fifo* fifo;
sem_t** sems;

#define SEMNAME "sem8"
#define ACTIONSEM "action8"
#define SHMNAME "shm8"
#define NNAME "N8"
#define AMMOUNT 10

void function() {
  counter++;
  sem_wait(semator_akcja);
  gettime();
  if (!isFullFifo(fifo)) {
    if (!isEmptyFifo(fifo))
      printf("%d , %d---%7d    Zajalem miejsce\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
    else
      printf("%d , %d---%7d   Zajalem pierwsze miejsce\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
    int index = pushFifo(fifo, getpid());
    printf("%d , %d---%7d      Czekam\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
    sem_post(semator_akcja);
    sem_post(semator_id);
    sem_wait(sems[index]);
    gettime();
    printf("%d , %d---%7d Zostalem ostrzyzony\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
  } else {
    printf("%d , %d---%7d  Nie ma wolnych miejsc\n", getpid(), (int) tp.tv_sec, (int) tp.tv_nsec);
    sem_post(semator_akcja);
  }
}


       int main(){

         size_t size = sizeof(struct Fifo);
         shmid = shm_open(SHMNAME, (O_RDWR), 0644); // przestrzen
         ftruncate(shmid, size);
         fifo = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);

         semator_akcja = sem_open(ACTIONSEM, (O_RDWR), 0644, 0);
         semator_id = sem_open(SEMNAME, (O_RDWR), 0644, 0);
         sems = malloc(N * sizeof(sem_t*));

         char name[AMMOUNT];
         for (int i=0; i<N; i++) {
           sprintf(name, "/%d", i);
           sems[i] = sem_open(name, (O_RDWR), 0644, 0);
         }

         for (int i=0; i<C; i++) {
           if (fork() == 0) {
             while (counter < S)
               function();
             return 0;
           }
         }
       return 0;
       }

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
#include<signal.h>

pthread_mutex_t mutex;
int filedes;
char *name;
int P;
int readed;
int N;
pthread_t * threads ;
int type;
int type2;
int x;

void function(int signo) {
    printf("signal: %d, PID: %u, TID: %lu\n", signo, getpid(), pthread_self());
}

	void * readLine(void * arg) {
if(type2==5){
    struct sigaction sigact;
    sigact.sa_handler = function;
    sigact.sa_flags = 0;

sigaction(SIGUSR1, &sigact, NULL);
sigaction(SIGTERM, &sigact, NULL);
sigaction(SIGKILL, &sigact, NULL);
sigaction(SIGSTOP, &sigact, NULL);
}
if(type2==4){
   sigset_t set;
   sigemptyset(&set);
sigaddset(&set, SIGUSR1);
sigaddset(&set, SIGTERM);
    pthread_sigmask(SIG_SETMASK, &set, NULL) ;
     }


char record[1025];
char * buff = (char *) malloc(P * 1024 * sizeof(char) + sizeof(char));

if(type==1) pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
else pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

if(type!=3)pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

int loop = 1;
	while (loop) {
		pthread_mutex_lock(&mutex);
		int readed = 0;
	  if ((readed = read(filedes, buff, P * 1024)) == 0) { // przytaj P rekordow
			loop = 0;
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
		int readed_lines = readed / 1024; // ile lini przeczytal

if(type2==6) x=1/0;

		for (size_t i = 0; i < readed_lines; i++) {
			strncpy(record, buff, 1024);  //kopiujemy do recordu
			memmove(buff, buff + 1024, P * readed_lines);  // przesuwamy wskaznik buff
			record[1024] = '\0';
			char * text;
			int id = strtol(record, &text, 10);  /// odseporowujemy id z text

		  if (strstr(text, name) != NULL) { //sprawdzamy czy name jest w text
		    printf("titd %ld o id%d \n", syscall(SYS_gettid), id);
					for(int i = 0; i < N; i++){
					      if(pthread_equal(threads[i], pthread_self()))  {
pthread_cancel(threads[i]);
}
						}
sleep(1);
	if(type!=3)loop = 0;
  }
}
if(type==2) pthread_testcancel();
		  }

return NULL;
}


	int main(int argc, char ** argv){

   N=atoi(argv[1]);
   char *path=argv[2];
   P=atoi(argv[3]);
   name=argv[4];
   type=atoi(argv[5]);
   type2=atoi(argv[6]);

if(type2==3){
    struct sigaction sigact;
    sigact.sa_handler = function;
    sigact.sa_flags = 0;

sigaction(SIGUSR1, &sigact, NULL);
sigaction(SIGTERM, &sigact, NULL);
sigaction(SIGKILL, &sigact, NULL);
sigaction(SIGSTOP, &sigact, NULL);
}
if(type2==2){
   sigset_t set;
   sigemptyset(&set);
sigaddset(&set, SIGUSR1);
sigaddset(&set, SIGTERM);



    pthread_sigmask(SIG_SETMASK, &set, NULL) ;
     }

    if((filedes = open(path, O_RDONLY)) == -1) {
     printf("Blad otwarcia");
return 0;
}


threads= calloc(N,sizeof(pthread_t));
pthread_mutex_init(&mutex, NULL);
 for(int i = 0;i < N; i++) {
     pthread_create(&(threads[i]), NULL, readLine, NULL);
  }

sleep(1);
//kill(getpid(), SIGUSR1);
//kill(getpid(), SIGTERM);
//kill(getpid(), SIGKILL);
// kill(getpid(), SIGSTOP);


 pthread_kill(threads[0], SIGUSR1);
//pthread_kill(threads[0], SIGTERM);
//pthread_kill(threads[0], SIGKILL);
// pthread_kill(threads[0], SIGSTOP);



for(int i = 0; i < N; i++) {
pthread_join(threads[i], NULL);
  }

close(filedes);
pthread_mutex_destroy(&mutex);
    return(0);
}

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

pthread_mutex_t mutex;
int filedes;
char *name;
int P;
int readed;
int N;
pthread_t * threads ;
int type;


	void * readLine(void * arg) {
char record[1025];
char * buff = (char *) malloc(P * 1024 * sizeof(char) + sizeof(char));

if(type!=2) pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
else pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

if(type!=3)pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
else pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

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
		for (size_t i = 0; i < readed_lines; i++) {
			strncpy(record, buff, 1024);  //kopiujemy do recordu
			memmove(buff, buff + 1024, P * readed_lines);  // przesuwamy wskaznik buff
			record[1024] = '\0';
			char * text;
			int id = strtol(record, &text, 10);  /// odseporowujemy id z text

		  if (strstr(text, name) != NULL) { //sprawdzamy czy name jest w text
		    printf("titd %ld o id%d \n", syscall(SYS_gettid), id);
					for(int i = 0; i < N; i++){
					      if(pthread_equal(threads[i], pthread_self())) { 
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



    if((filedes = open(path, O_RDONLY)) == -1) {
     printf("Blad otwarcia");
return 0;
}


threads= calloc(N,sizeof(pthread_t));
pthread_mutex_init(&mutex, NULL);
 for(int i = 0;i < N; i++) {
     pthread_create(&(threads[i]), NULL, readLine, NULL);
  }

for(int i = 0; i < N; i++) {
pthread_join(threads[i], NULL);
  }
free(threads);
close(filedes);
pthread_mutex_destroy(&mutex);
    return(0);
}

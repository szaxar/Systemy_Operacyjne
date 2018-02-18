#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

using namespace std;
pid_t PPID;
int counter=0;
pid_t *tab; // tablica oczekujacych
int K;
clock_t start;
	void foo(int sig,siginfo_t *siginfo, void *context){
start = ((1000*clock())/CLOCKS_PER_SEC);
cout<<"otrzymano sygnal"<<siginfo->si_signo<<" prosba o przejscie sygnalu o pid"<<siginfo->si_pid<<endl;


if(counter<K)tab[counter]=siginfo->si_pid;
counter++;
if(counter==K) for(int j=0;j<K;j++) kill(tab[j],SIGUSR2);
if(counter>K) kill(siginfo->si_pid,SIGUSR2);

}


	void doo(int sig,siginfo_t *siginfo, void *context){
cout<<"otrzymano sygnal"<<siginfo->si_signo<<" otrzymano pozwolenie dla sygnalu "<<getpid()<<endl;
kill(PPID,SIGRTMIN+rand()%32);

}

	void hoo(int sig,siginfo_t *siginfo, void *context){
 
cout<<"zakonczenie sygnalu"<<siginfo->si_pid<<" wylosowano sygnal "<<siginfo->si_signo<<" czas trwania procesu to "<<clock()-start<<endl;
}

	int main( int argc, char ** argv){
int n=atoi(argv[1]);
K=atoi(argv[2]);

tab=(pid_t*)malloc(sizeof(pid_t)*n);

struct sigaction act;
act.sa_sigaction=&foo;
sigemptyset (&act.sa_mask);
act.sa_flags=SA_SIGINFO;
sigaction(SIGUSR1,&act,NULL);


struct sigaction act2;
act2.sa_sigaction=&doo;
sigemptyset (&act2.sa_mask);
act2.sa_flags=SA_SIGINFO;
sigaction(SIGUSR2,&act2,NULL);


struct sigaction act3;
act3.sa_sigaction=&hoo;
sigemptyset (&act3.sa_mask);
act3.sa_flags=SA_SIGINFO;

PPID=getpid();

for(int k=0;k<32;k++) sigaction(SIGRTMIN+k,&act3,NULL);


	for(int i=0;i<n;i++){
pid_t pid=fork();
	if(pid==0) {
sleep(rand()%10);
kill(PPID,SIGUSR1);
pause();
exit(0);
}
	else {
if(pid>0){
pause();

}
}
}
while(true){
}
   return 0 ;

}

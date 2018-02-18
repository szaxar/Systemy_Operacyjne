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

union sigval value;
union sigval value2;
int counter1=0;
int counter2=0;
int counter3=0;
int L;
int x;
void dziecko(int sig,siginfo_t *siginfo, void *context){
counter2++;
if(x!=2)kill(getppid(),sig);
else sigqueue(getppid(),sig,value);
}

void koniec(int sig,siginfo_t *siginfo, void *context){
cout<<" Dziecko odebralo :"<<counter2<<endl;
exit(1);
}

void rodzic(int sig,siginfo_t *siginfo, void *context){
counter3++;
}



	int main( int argc, char ** argv){
x=atoi (argv[1]);
L=atoi (argv[2]);

struct sigaction act;
act.sa_sigaction=&dziecko;
sigemptyset (&act.sa_mask);
act.sa_flags=SA_SIGINFO;

struct sigaction act2;
act2.sa_sigaction=&koniec;
sigemptyset (&act2.sa_mask);
act2.sa_flags=SA_SIGINFO;
	

struct sigaction act3;
act3.sa_sigaction=&rodzic;
sigemptyset (&act3.sa_mask);
act3.sa_flags=SA_SIGINFO;



pid_t PPID=getpid();
pid_t pid;

switch(x){
case 1:
pid=fork();
if(pid==0){
sigaction(SIGUSR1, &act,NULL);
sigaction(SIGUSR2, &act2,NULL);
for (;;) {}
}
else{
sigaction(SIGUSR1, &act3,NULL);
sleep(1);
for(int i=0;i<L;i++){
counter1++;
kill(pid,SIGUSR1);
}
kill(pid,SIGUSR2);
}		
break;

case 2:

pid=fork();
if(pid==0){
value.sival_int=5;
value.sival_ptr=(void*)dziecko;
value2.sival_int=6;
value2.sival_ptr=(void*)koniec;
sigaction(SIGUSR1, &act,NULL);
sigaction(SIGUSR2, &act2,NULL);
for (;;) {}
}
else{
sigaction(SIGUSR1, &act3,NULL);
value.sival_int=5;
value.sival_ptr=(void*)rodzic;
sleep(1);
for(int i=0;i<L;i++){
counter1++;
sigqueue(pid,SIGUSR1,value);
}
sigqueue(pid,SIGUSR2,value2);
}
break;

case 3:
pid=fork();
if(pid==0){
sigaction(SIGRTMIN, &act,NULL);
sigaction(SIGRTMIN+1, &act2,NULL);
for (;;) {}
}
else{
sigaction(SIGRTMIN, &act3,NULL);
sleep(1);
for(int i=0;i<L;i++){
counter1++;
kill(pid,SIGRTMIN);
}
kill(pid,SIGRTMIN+1);
}

break;



}


cout<<"Wyslano: "<<counter1<<" Rodzic odebral: "<<counter3<<endl;


return 0;
}

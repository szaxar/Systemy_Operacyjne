
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

static int x=65;
static int flag=1;

 void foo (int sig){
if(sig==SIGINT){
//cout<<endl<<"Odebrano sygnał"<<sig;
exit(1);
}

if(sig==SIGTSTP){
if(flag==1) flag=0;
else flag=1;
}
if(flag){
	if(x==90) x=65;
	else x++;
}
else {
if(x==65) x=90;
else x--;

}
}

 
int main (int argc, char *argv[])
{

	struct sigaction act;
	act.sa_handler=foo;
	sigemptyset (&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGTSTP,&act,NULL);
	signal(SIGINT,foo);


while(1==1){
	printf("%c\n",(char)x);
		foo(0);
	
		sleep(1);
 }

	return 0;
}

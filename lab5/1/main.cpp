#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
using namespace std;

int MAXLINE=50;
int tab[2];
char *tablica[20];
#define READ_END 1
#define WRITE_END 0
pid_t pid;
char *argumenty[3];
char *nazwa;

void _do(char *name,char **argumenty,int index,int in,int out){
pid=fork();
if(pid==0){
	if(index==0){
		if(out!=STDIN_FILENO){
			dup2(out,STDOUT_FILENO);
			close(out);
		}
	}
else{
	if(in !=STDIN_FILENO){
		dup2(in,STDIN_FILENO);
		close(in);
	}
	if(out!=STDIN_FILENO){
		dup2(out,STDOUT_FILENO);
		close(out);
	}
}

if(execvp(name,argumenty)==-1){
	cout<<"blad"<<endl;
	exit(1);

}
}
else {
	int status;
	wait(&status);
	close(in);
}
}


	void czynnosc(string z){
const char *y=z.c_str();
char *x=strdup(y);
char *arg=strtok(x,"|");
int tmp=0;
cout<<"Spradzwa ile |";
while (arg!=NULL){
tablica[tmp]=arg;
arg=strtok(NULL,"|");
tmp++;
}
cout<<tmp<<endl; /// ile |
int in=STDIN_FILENO;

for(int j=0;j<tmp;j++){
	int tmp=-1;
	char *arg=strtok(tablica[j]," ");
	char *argumenty[3];
	char *nazwa;
	while (arg!=NULL){
		if(tmp==-1){
		nazwa=arg;
		tmp=0;
	}
	else {
		argumenty[tmp-1]=arg;
		arg=strtok(NULL," ");
		tmp++;
	}
	}
	cout<<nazwa<<" "<<argumenty[0]<<endl;


pipe(tab);
_do(nazwa,argumenty,j,in,tab[READ_END]);
close(tab[READ_END]);
in=tab[WRITE_END];
}

pid_t last=fork();
if(last==0){
	if(in!=STDIN_FILENO){
		dup2(in,STDIN_FILENO);
		close(in);
	}

	if(execvp(nazwa,argumenty)==-1){
		cout<<"blad";
		exit(1);
	}
	else {
		int status;
		wait(&status);
	}
}

}

int main(int argc, char ** argv){

    fstream plik;
    plik.open( argv[1], ios::in );

    if( plik.good() )
    {
        string napis;
        while( !plik.eof() )
        {
            getline( plik, napis );
           czynnosc(napis);
        }
        plik.close();
    } else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    return( 0 );
}

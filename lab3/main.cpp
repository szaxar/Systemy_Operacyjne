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



void zmienna(string z){

int k=-1;
int tmp=0;
for(int i=0;i<z.size();i++){
if(z[i]==' '){
k=i;
tmp++;
}
}

if(tmp>2) cout<<"blad";
if(tmp==1) {
string nazwa=z.substr(1,k);
string zawartosc=z.substr(k+1,z.size());
 char *name=new char[nazwa.size()+1];
strcpy(name, nazwa.c_str());
 char *value=new char[zawartosc.size()+1];
strcpy(value, zawartosc.c_str());

setenv(name,value,1);
cout<<nazwa<<" "<<getenv(name)<<endl;
}
if(tmp==0) {string nazwa=z.substr(1,k);

 char *name=new char[nazwa.size()+1];
strcpy(name, nazwa.c_str());

unsetenv(name);
cout<<"Usuwanie"<<endl;
}
}


		void czynnosc(string z,int x){
if(z.size()>1){
pid_t pid = fork();
rusage r;
int status = 0;

	if(pid ==0){

static rlimit memoryLimit;
static rlimit timeLimit;
memoryLimit.rlim_cur = memoryLimit.rlim_max =(rlim_t) x;
timeLimit.rlim_cur = timeLimit.rlim_max =(rlim_t) x;
int j=z.size()+1;
int tmp=0;
for(int i=0;i<z.size();i++){
if(z[i]==' '){
if(tmp==0) j=i;
tmp++;
}
}


string nazwa=z.substr(0,j);
 char *name=new char[nazwa.size()];
strcpy(name, nazwa.c_str());
const char *name1=name;

const char *arg[tmp];
int i=0;
int x=j+1;


while(x<z.size()+1){
if(z[x]==' ') {
arg[i]=z.substr(j+1,x).c_str();
j=x;
i++;

}
x++;

}
arg[tmp-1]=NULL;
char *args[tmp];
for(int i=0;i<tmp;i++) args[i]=const_cast<char *>(arg[i]);

int a=execve(name1,args,environ);

}
else if(pid>0) {
pid=wait3(&status, 0, &r);
if(WEXITSTATUS(status) != 0) cout<<"blad";
}

}

}

int main(int argc, char ** argv){
    fstream plik;
extern char **environ;
int x=atoi(argv[2]);
    plik.open( argv[1], ios::in );
	
    if( plik.good() )
    {
        string napis;
       
        while( !plik.eof() )
        {

            getline( plik, napis );
            if(napis[0]=='#') zmienna(napis);
	else czynnosc(napis,x);

        }
        plik.close();
    } else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
   
   
    return( 0 );
}

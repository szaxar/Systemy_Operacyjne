#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include <iostream>
#include <time.h>
#include <unistd.h>


///serwer
char *tab[500];
int counter=1;

 mqd_t mq2[10];  ///koleka prywatna
int size(int x){
int tmp=0;
while(x>0){
tmp++;
x=x/10;
}
return tmp;
}
int power(int x){
int tmp=1;
for(int i=0;i<x;i++){
tmp=tmp*10;
}
return tmp;
}

using namespace std;
int main(int argc, char **argv)
{


int klient;
	const char *type; ///typ
    mqd_t mq;   ///kolejka glowna
    struct mq_attr attr;
    char buffer[1024 + 1];
    int must_stop = 0;


    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    cout<<"Otwarto serwer: "<<endl;
    mq = mq_open("/test_queue", O_CREAT | O_RDONLY, 0644, &attr); // owarcie kolejki do otrzymywania pid


  do {
     	ssize_t bytes_read;
        bytes_read = mq_receive(mq, buffer, 1024, NULL);
        buffer[bytes_read] = '\0';
        type=&buffer[0];


      cout<<"Otrzymano "<<buffer<<endl;
int tmptype;
if(atoi(type)>100) tmptype=0;
else {
tmptype=atoi(type)/10;
klient=atoi(type)%10;
cout<<"od uzytkownika"<<klient<<endl;
}

switch(tmptype){
case 0:
{
      cout<<"otrzymano pid"<<buffer<<"przydzielono nr"<<counter<<endl;  //otrzymanie pid
      buffer[0]='/';
cout<<"lacze sie z uzytkownikiem"<<buffer<<endl;
sleep(2);
    mq2[counter] = mq_open( buffer, O_WRONLY); //otwiera kolejke
tab[counter]=buffer;
//tab[counter]=buffer;
cout<<"Klient "<<tab[counter]<<endl;
char tmp2[50];
sprintf(tmp2,"%d",counter);
cout<<"Wysylam nr"<<tmp2<<endl;
mq_send(mq2[counter], tmp2, 1024, 0);
	counter++;
}
break;
case 1: //echo
cout<<"Wyslano"<<buffer<<endl;
mq_send(mq2[klient], buffer, 1024, 0);
break;

case 2:  //duze
char tmp[1024];
for(int i=1;i<6;i++){
if(buffer[i]>96 && buffer[i]<123) tmp[i-1]=(char)(buffer[i]-32);
else tmp[i-1]=buffer[i];
}
strcpy(buffer,tmp);
  cout<<"Wyslano"<<buffer<<endl;
mq_send(mq2[klient], buffer, 1024, 0);
break;

case 3:  //czas
{
time_t czas;
time(&czas);
tm *t=localtime(&czas);
char *_time= asctime( t);
strcpy(buffer,_time);
cout<<"Wyslano czas "<<buffer<<endl;
mq_send(mq2[klient], buffer, 1024, 0);
}
break;

case 4:
cout<<"Zamykam"<<endl;

break;



}




    } while (atoi(type)!=4);

  mq_close(mq);


  mq_unlink("/test_queue");
for(int i=1;i<counter;i++){
mq_close(mq2[i]);
mq_unlink(tab[i]);
}

    return 0;
}

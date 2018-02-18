 #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>
       #include <iostream>
       #include <string.h>
       #include <stdlib.h>
       #include <sys/shm.h>
#include <stdio.h>
#include<unistd.h>
#include <time.h>



       struct bufor{
       long typ;
       char wartosc[32];
       };
       ///serwer
        using namespace std;
	int id[10];

    int main(){

	int counter=1;
	int klienci[500];
        key_t klucz=ftok(getenv("HOME"),'p'); //klucz

	int idserwera=msgget(klucz,IPC_CREAT | 0600); ////id
	cout<<"klucz serwera"<<klucz<<" id serwera"<<idserwera<<endl;
        struct bufor buf2;
        int rozmiar=sizeof(bufor)-sizeof(long);
  	bool flaga=true;

while(flaga){
	sleep(5);
	msgrcv(idserwera,&buf2,rozmiar,0,NULL);
	cout<<"otrzymano typ"<<buf2.typ<<" wartosc"<<buf2.wartosc<<endl;

switch(buf2.typ%10){
case 1:  /// login
{
id[counter]=msgget(atoi(buf2.wartosc),IPC_CREAT | 0600); ////idklienta
cout<<"klucz klienta"<<buf2.wartosc<<" id klienta"<<id[counter]<<endl;

struct bufor buf;
    buf.typ=1;
    char klucz1[32]; ///klucz_char
    sprintf(klucz1,"%d",counter);
    strcpy(buf.wartosc,klucz1);
    klienci[counter]=atoi(buf2.wartosc);
    cout<<"wysylam typ"<<buf.typ<<" nr klienta"<<counter<<endl;
    msgsnd(id[counter],&buf,rozmiar,0); ///wyslanie
    counter++;
}
break;

case 2: ///echo
  cout<<"wysylam typ"<<buf2.typ<<" wartosc"<<buf2.wartosc<<buf2.wartosc<<"do klienta"<<buf2.typ/10<<endl;
 msgsnd(id[buf2.typ/10],&buf2,rozmiar,0);
break;

case 3: ///wszystkie duze
char tmp[32];
for(int i=0;i<sizeof(buf2.wartosc)/sizeof(char);i++){
if(buf2.wartosc[i]>96 && buf2.wartosc[i]<123) tmp[i]=(char)(buf2.wartosc[i]-32);
}
strcpy(buf2.wartosc,tmp);
  cout<<"wysylam typ"<<buf2.typ<<" wartosc"<<buf2.wartosc<<"do klienta"<<buf2.typ/10<<endl;
 msgsnd(id[buf2.typ/10],&buf2,rozmiar,0);
break;

case 4:  //czas 
{
time_t czas;
time(&czas);
tm *t=localtime(&czas);
char *_time= asctime( t);
strcpy(buf2.wartosc,_time);
cout<<"wysylam typ"<<buf2.typ<<" wartosc"<<buf2.wartosc<<buf2.wartosc<<"do klienta"<<buf2.typ/10<<endl;
msgsnd(id[buf2.typ/10],&buf2,rozmiar,0);
}
break;

case 5:
flaga=false;
msgctl(id[buf2.typ/10],IPC_RMID,NULL);
break;
}
  
}

       return 0;
       }

 #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>
       #include <iostream>
       #include <string.h>
       #include <stdlib.h>
       #include <sys/shm.h>
       #include <stdio.h>
       #include<unistd.h>
       struct bufor{
       long typ;
       char wartosc[32];
       };
       ////klient
       using namespace std;

    int main(){

	int x=2;
	pid_t pid=getpid();
int counter=0;
      key_t klucz=ftok(getenv("HOME"),'p'); ///klucz
      int idserwera=msgget(klucz,IPC_CREAT | 0600); ////idserwera
cout<<"klucz serwera"<<klucz<<" id serwera"<<idserwera<<endl;      

key_t klucz2=pid;
int id=msgget(klucz2,IPC_CREAT | 0600);
cout<<"klucz klienta"<<klucz2<<" id klienta"<<id<<endl;  

   struct bufor buf; ///bufor
int rozmiar=sizeof(bufor)-sizeof(long); ///rozmiar
 buf.typ=1;   //typ
 sprintf(buf.wartosc,"%d",pid);  //kopiowanie pid do char[32]
  cout<<"wysylam typ"<<buf.typ<<" wartosc"<<buf.wartosc<<endl; // wysylam pid
   msgsnd(idserwera,&buf,rozmiar,0); ///wyslanie 
   sleep(5); //uspienie

 struct bufor odebrane;
  struct bufor odebrane2;
    msgrcv(id,&odebrane,rozmiar,0,IPC_NOWAIT);  //odebranie countera
    cout<<"Otrzymano typ"<<odebrane.typ<<" uzytkownik ma nr"<<odebrane.wartosc<<endl;
counter=atoi(odebrane.wartosc);
sleep(5);
while(1){

buf.typ=counter*10+x;   /// counter + typ
x++;
strcpy(buf.wartosc,"xxXX");  //wiadomosc 
cout<<"wysylam typ"<<buf.typ<<" wartosc"<<buf.wartosc<<endl; 
 msgsnd(idserwera,&buf,rozmiar,0); ///wyslanie

if(buf.typ%10==5) break;
sleep(5);

  msgrcv(id,&odebrane2,rozmiar,0,IPC_NOWAIT);
  cout<<"Otrzymano wartosc"<<odebrane2.wartosc<<endl;
}

       return 0;
       }

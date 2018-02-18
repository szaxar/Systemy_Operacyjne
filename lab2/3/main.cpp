#include<iostream>
#include <sys/stat.h>
#include <sys/file.h>
#include  <sys/types.h>
#include  <unistd.h>
#include  <fcntl.h>
//int  fcntl(int  filedes , int cmd , .../* int  arg */);
//int flock(unsigned int fd    /* deskryptor pliku */   unsigned int cmd   /* komenda */); 
//int  open(const  char* pathname , int oflag , .../*, mode_t  mode */);



#include <string>
using namespace std;
struct node{
node *next;
const char* path;
int x;
};

node *add(node *first,const char* p,int v){
if(first==NULL) {
first->path=p;
first->x=v;
return first;
}
else{
node*a=new node;
a->next=first;
a->path=p;
a->x=v;
return a;
}
}

void show(node *first){
while (first->next!=NULL) cout<<first->path;
}


node * _delete(node *first, const char *p, int v){
if(first->path==p && first->x==v){
node *p=first;
first=p->next;
delete p;
}
else {
while(first->next!=NULL){
if(first->next->path==p && first->next->x==v){
node *p=first->next;
first->next=p->next;
delete p;

}
}

}

return first;
}

int _read(const char *pathname){
char res[256];
int deskryptor=open(pathname,O_RDONLY);
int x=read(deskryptor, res,1);
return x;
}

size_t _write(const char *pathname){

char res[256];
int deskryptor=open(pathname,O_WRONLY);
size_t x=write(deskryptor,res,1);
return x;
}

void block1(const char *pathname){

int deskryptor=open(pathname,O_RDONLY);

if(deskryptor !=-1){

int x=flock(deskryptor,LOCK_EX);	

}
}


void block2(const char *pathname){

int deskryptor=open(pathname,O_WRONLY);
if(deskryptor !=-1){

int x=flock(deskryptor,LOCK_EX);	

}
}

void unblock(const char *pathname){

int deskryptor=open(pathname,O_RDWR);

if(deskryptor !=-1){

int x=flock(deskryptor,LOCK_UN);	

}

}

int main(){
int x ;
int r;
node *first=NULL;
const char *path="/home/szaxar/Pulpit/sys/lab2/3/a.lock";
  cout<<"1.  ustawienie rygla do odczytu na wybrany znak pliku,"<<endl;
   cout<<"2. ustawienie rygla do zapisu na wybrany znak pliku,"<<endl;
   cout<<"3. wyświetlenie listy zaryglowanych znaków pliku (z informacją o numerze PID procesu .będącego właścicielem rygla oraz jego typie - odczyt/zapis),"<<endl;
  cout<<"4.  zwolnienie wybranego rygla,"<<endl;
   cout<<"5. odczyt (funkcją read) wybranego znaku pliku,"<<endl;
   cout<<"6. zmiana (funkcją write) wybranego znaku pliku."<<endl;

cin>>x;


switch(x){
case 1:

block1(path);
first=add(first,path,x);
break;


case 2:
block2(path);
first=add(first,path,x);
break;


case 3:
show(first);
break;

case 4:
unblock(path);
first=_delete(first,path,1);
break;


case 5:
r=_read(path);
break;


case 6:
size_t w=_write(path);
break;



}
return 0;



}

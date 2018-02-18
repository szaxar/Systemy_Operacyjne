#include <time.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include  <stdlib.h>
#include  <stdio.h>
using namespace std;
int len(int x){
int tmp=0;
while (x>0){
      x=x/10;
      tmp++;
}
      return tmp;
      }

        int power(int x){
        int tmp=1;
        for(int i=0;i<x;i++) tmp=tmp*10;
        return tmp;
        }


struct data{
int year;
int month;
int day;
};

struct person{
string firstName;
string lastName;
data dateOfBirth;
string email;
int number;
};


struct node{
node *next;
node *prev;
person p;
};

bool equality(person p1 , person p2){

if(p1.firstName==p2.firstName && p1.lastName==p2.lastName &&
    p1.email==p2.email && p1.number==p2.number &&
    p1.dateOfBirth.year==p2.dateOfBirth.year &&
    p1.dateOfBirth.month==p2.dateOfBirth.month &&
    p1.dateOfBirth.day==p2.dateOfBirth.day) return true;
        else return false;

}

node *make(person p1){

node *first=new node;
first->next=NULL;
first->prev=NULL;
first->p=p1;
return first;
}

node *add(node *first,person p1){
node *f=new node;
f->next=first;
f->prev=NULL;
f->p=p1;
first->prev=f;
return f;

}

void show(node *first){

while(first!=NULL) {
      cout<<first->p.firstName<<" , "<<first->p.lastName<<" ,"<<first->p.number<<" , "<<first->p.email<<endl;
      first=first->next;
      }
}

node * get(node *first , person val ){

if(equality(first->p,val)) return first;
else{
while(first->next!=NULL){
        if(equality(first->next->p,val)) return first->next;
        first=first->next;
}
        return first;
}
}

node* _delete(node *first,person p1){

if(equality(first->p,p1)){
    node *q=first->next;
    delete first;
    q->prev=NULL;
    return q;
}else{

    node *q=first;

while(first->next!=NULL ){

   if(equality(first->next->p,p1)) {
    node *q=first->next;
    first->next=q->next;
    q->next->prev=first;
    delete q;
    break;
   }
   first=first->next;
}
return q;
}


}





bool check(person p1 , person p2 , string z){

int x=0;
int x2=0;
        string a;
        string b;
        if(z=="firstName")  {
                a=p1.firstName;
                b=p2.firstName;
        }
         if(z=="lastName")  {
                a=p1.lastName;
                b=p2.lastName;
         }
          if(z=="email")  {
                a=p1.email;
                b=p2.email;
          }

if(z=="firstName" || z=="lastName" || z=="email"){
for(int i=0;i<min(a.length(),b.length());i++){
    x=x*power(len((int) a.at(0)))+(int)a.at(i);
    x2=x2*power(len((int) b.at(0)))+(int)b.at(i);
}
}

else if(z=="dateOfBirth"){
    x=p1.dateOfBirth.year*366+p1.dateOfBirth.month*30+p1.dateOfBirth.day;
    x2=p2.dateOfBirth.year*366+p2.dateOfBirth.month*30+p2.dateOfBirth.day;
} else {
    x=p1.number;
    x2=p2.number;
}
if(x>x2) return true;
else return false;

}



void _switch(node *l1 , node *l2){
person p1=l1->p;
l1->p=l2->p;
l2->p=p1;
}

node *_sort(node *first,string z){

node *p;
int changed=1;
while(changed){
        changed=0;
    for(p=first;p->next;p=p->next){
    if(check(p->p,p->next->p,z)){
        _switch(p,p->next);
        changed=1;
    }

}
}
return first;

}

int ile(node *first){
int tmp=0;
while(first!=NULL){
    tmp++;
    first=first->next;
}
return tmp;
}

void _deleteall(node *first){
node *tmp;
for(int j=0;j<ile(first);j++){

        tmp=first->next;
    delete first;
    node *first=tmp;
}
delete tmp;
}

person getLast(node *first){
while(first->next->next!=NULL) first=first->next;
return first->p;
}


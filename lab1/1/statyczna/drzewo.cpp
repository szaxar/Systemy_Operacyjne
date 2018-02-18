#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
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
person key;
node *lewy;
node *prawy;
node *rodzic;
}*korzen=NULL;


bool equality(person p1 , person p2){

if(p1.firstName==p2.firstName && p1.lastName==p2.lastName &&
    p1.email==p2.email && p1.number==p2.number &&
    p1.dateOfBirth.year==p2.dateOfBirth.year &&
    p1.dateOfBirth.month==p2.dateOfBirth.month &&
    p1.dateOfBirth.day==p2.dateOfBirth.day) return true;
        else return false;

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

node *naj_lewo(node *root){
while(root->lewy!=NULL) root=root->lewy;
return root;
}

void push(node *&korzen,node *rod,person x,string z){

     if(korzen==NULL){
        korzen=new node;
       korzen->lewy=NULL;

       korzen->prawy=NULL;
       korzen->key=x;
       korzen->rodzic=rod;
       return;
       }else{
            if(check(korzen->key,x,z))
            push(korzen->lewy,korzen,x,z);
            else push(korzen->prawy,korzen,x,z);
            }
}



void show(node *korzen){
if(korzen){
          show(korzen->lewy);
cout<<korzen->key.firstName;
          show(korzen->prawy);
}
}


void deleteall(node *root){
    if(root){
        deleteall(root->lewy);
        deleteall(root->prawy);
    }
    delete root;
}

node *get(node *root, person val,string z){
if(equality(root->key,val)) return root;
else if(check(root->key,val,z)) get(root->lewy,val,z);
    else get(root->prawy,val,z);

}



void kasowanie( node *start){

if(start->lewy==NULL && start->prawy==NULL){
if(start->rodzic==NULL){
korzen=NULL;
}else if(start->rodzic->lewy==start){
start->rodzic->lewy=NULL;
}
else{
start->rodzic->prawy=NULL;
}
delete start;
}

else if(start->lewy==NULL || start->prawy==NULL){
if(start->lewy==NULL){
if(start->rodzic==NULL){
start=start->prawy;
}
else if(start->rodzic->lewy==start){
start->rodzic->lewy=start->prawy;
}
else{
start->rodzic->prawy=start->prawy;
}
}
else{
if(start->rodzic==NULL){
start=start->lewy;
}
else if(start->rodzic->lewy==start){
start->rodzic->lewy=start->lewy;
}
else{
start->rodzic->prawy=start->lewy;
}
}
delete start;
}
else
{
node *temp;
temp=naj_lewo(start->prawy);
start->key = temp->key;
kasowanie(temp);
}
}
void _do(node *korzen,node *tmp , string z ){
push(tmp,NULL,korzen->key,z);
if(korzen->lewy!=NULL) _do(korzen->lewy,tmp,z);
if(korzen->prawy!=NULL) _do(korzen->prawy,tmp,z);

}


node *remake(node *korzen,string z){
node *tmp =new node;
tmp->lewy=NULL;
tmp->prawy=NULL;

_do(korzen,tmp,z);
deleteall(korzen);

return tmp;
}




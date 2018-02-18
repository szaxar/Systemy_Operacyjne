

#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "lista.h"

int main(){

    string imie[17]={"adam","kuba","andrzej","stansilaw","wiktor","ola","aleksandra","fhtstqzeof"
"htncmfvzdf","ybjfrzpwot","pxytibwhjv","rrlawiyntj","kipgbsinfh",
"dszazxfwbf","vkpwsiubmq","pkuszmdmlt","nciqelmglu"};




string nazwiska[10]={"ararpslchz","flzihvwpyy","bfkiocudmz",
"suebzpekow","gzmnjxdchy","uiqvnoapkg","odhwzfqsrm","joxpdlljqn",
"wascltwhhk","asmapsooyv"};
person p;
person p1;


 clock_t start = ((1000*clock())/CLOCKS_PER_SEC);

 p1.firstName=imie[rand() %17];
    p1.lastName=nazwiska[rand()%10];
    p1.dateOfBirth.day=rand()%30+1;
    p1.dateOfBirth.month=rand()%12+1;
    p1.dateOfBirth.year=rand()%30+1960;
    p1.number=rand()%100000000+1000000000;
    p1.email=nazwiska[rand()%10];

    node *first=make(p1);

 printf( "Czas stworzenia listy: %lu ms\n", clock() - start );
 start = ((1000*clock())/CLOCKS_PER_SEC);

for(int i=0;i<999;i++){
    p.firstName=imie[rand() %17];
    p.lastName=nazwiska[rand()%10];
    p.dateOfBirth.day=rand()%30+1;
    p.dateOfBirth.month=rand()%12+1;
    p.dateOfBirth.year=rand()%30+1960;
    p.number=rand()%100000000+1000000000;
    p.email=nazwiska[rand()%10];
  first=add(first,p);
}

 printf( "Czas wykonywania dodawania na liscie: %lu ms\n", clock() - start );
   start = ((1000*clock())/CLOCKS_PER_SEC);



node *tmp;
node *tmp2;

tmp=get(first,p1);
 printf( "Czas szukania  na liscie(pesmistyczny): %lu ms\n", clock() - start );
   start = ((1000*clock())/CLOCKS_PER_SEC);
tmp2=get(first,p);
 printf( "Czas szukania  na liscie(optymistyczny): %lu ms\n", clock() - start );
   start = ((1000*clock())/CLOCKS_PER_SEC);

_delete(first,first->p);
 printf( "Czas usuwania  na liscie(optymistyczny): %lu ms\n", clock() - start );
   start = ((1000*clock())/CLOCKS_PER_SEC);
_delete(first,getLast(first));
 printf( "Czas usuwania  na liscie(pesymistyczny): %lu ms\n", clock() - start );
   start = ((1000*clock())/CLOCKS_PER_SEC);
first=_sort(first,"lastName");
 printf( "Czas sorotwania  na liscie: %lu ms\n", clock() - start );
   start = ((1000*clock())/CLOCKS_PER_SEC);
_deleteall(first);
 printf( "Czas usuwania  listy: %lu ms\n", clock() - start );
    return 0;
}

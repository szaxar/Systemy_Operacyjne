
#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "drzewo.h"
#include <dlfcn.h>



int main(){

    string imie[17]={"adam","kuba","andrzej","stansilaw","wiktor","ola","aleksandra","fhtstqzeof"
"htncmfvzdf","ybjfrzpwot","pxytibwhjv","rrlawiyntj","kipgbsinfh",
"dszazxfwbf","vkpwsiubmq","pkuszmdmlt","nciqelmglu"};

string nazwiska[10]={"ararpslchz","flzihvwpyy","bfkiocudmz",
"suebzpekow","gzmnjxdchy","uiqvnoapkg","odhwzfqsrm","joxpdlljqn",
"wascltwhhk","asmapsooyv"};

 clock_t start = ((1000*clock())/CLOCKS_PER_SEC);

person p;
for(int i=0;i<1000;i++){
    p.firstName=imie[rand() %17];
    p.lastName=nazwiska[rand()%10];
    p.dateOfBirth.day=rand()%30+1;
    p.dateOfBirth.month=rand()%12+1;
    p.dateOfBirth.year=rand()%30+1960;
    p.number=rand()%100000000+1000000000;
    p.email=nazwiska[rand()%10];
    push(korzen,NULL,p,"firstName");
}
 printf( "Czas wykonywania dodawania na drzewie: %lu ms\n", clock() - start );
   start = ((1000*clock())/CLOCKS_PER_SEC);


   node *tmp=get(korzen,korzen->key,"firstName");
 printf( "Czas szukania  na drzewie(optymistyczny): %lu ms\n", clock() - start );
    start = ((1000*clock())/CLOCKS_PER_SEC);

   node *tmp2=get(korzen,naj_lewo(korzen)->key,"firstName");
 printf( "Czas szukania  na drzewie(pesymistyczny): %lu ms\n", clock() - start );

kasowanie(korzen);
 printf( "Czas wykonywania kasowania na drzewie(optymistyczny): %lu ms\n", clock() - start );
 start = ((1000*clock())/CLOCKS_PER_SEC);
kasowanie(naj_lewo(korzen));
 printf( "Czas wykonywania kasowania na drzewie(pesymistyczny): %lu ms\n", clock() - start );
  start = ((1000*clock())/CLOCKS_PER_SEC);
korzen=remake(korzen,"lastName");
 printf( "Czas wykonywania remaku na drzewie %lu ms\n", clock() - start );
  start = ((1000*clock())/CLOCKS_PER_SEC);
deleteall(korzen);
printf( "Czas kasowania drzewa : %lu ms\n", clock() - start );


system("PAUSE");

}

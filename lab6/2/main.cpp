#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;
////klient
int size(int x){
int tmp=0;
while(x>0){
tmp++;
x=x/10;
}
return tmp;
}

int main(){
	srand(time(NULL));
	char pid[50];
	memset(pid, 0, 50);
	sprintf(pid,"%d%d",0,getpid());  //pid
	mqd_t mq;
	char buffer[1024];
	int x;
 char tmp[6]={"XXXxx"};
cout<<"lacze sie z serwerem"<<endl;
    mq = mq_open( "/test_queue", O_WRONLY); //otwiera kolejke

  cout<<"Send to server :"<<pid<<endl;
mq_send(mq, pid, 50, 0);

 mqd_t mq2;
    struct mq_attr attr2;
    char buffer2[1024 + 1];
    int must_stop2 = 0;

    attr2.mq_flags = 0;
    attr2.mq_maxmsg = 10;
    attr2.mq_msgsize = 1024;
    attr2.mq_curmsgs = 0;

pid[0]='/';
    cout<<"otwieram serwer o nazwie "<<pid<<endl;
    mq2 = mq_open(pid, O_CREAT | O_RDONLY, 0644, &attr2);  //otwarcie kolejki

cout<<"Czekam na przydzielenie nr"<<endl;
ssize_t bytes_read;
bytes_read = mq_receive(mq2, buffer2, 1024, NULL);
buffer2[bytes_read] = '\0';
 printf("Received nr: %s\n", buffer2);

char nr=buffer2[0];

do{
	sleep(5);
        x=rand()%4+1;
  memset(buffer, 0, 1024);
	buffer[0]=x+'0';
	buffer[1]=nr;
for(int i=0;i<5;i++){
buffer[i+2]=tmp[i];
}

    cout<<"Wysylam"<<buffer<<endl;
       mq_send(mq, buffer, 1024, 0);
sleep(2);
 bytes_read = mq_receive(mq2, buffer2, 1024, NULL);
buffer2[bytes_read] = '\0';
 printf("Received: %s\n", buffer2);

    } while (x!=4);

    mq_close(mq2);

    return 0;
}

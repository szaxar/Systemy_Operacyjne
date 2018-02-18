#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include<sys/shm.h> 
#include<sys/ipc.h> 
#include<signal.h>
#include <sys/sem.h>
#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <poll.h>
#include <sys/un.h>
struct Client{
int fd;
char name[50];
};
typedef enum operator {
	ADD = 1,
	SUBTRACT = 2,
	MULTIPLY = 3,
	DIVIDE = 4,
	PING = 5,
	NAME = 6,
	EXIT = 7,
	ACCEPT = 8,
	DENY = 9
}operator;
typedef struct operation { 
	int arg1;
	int arg2;
	int arg3;
	char name[50];
	operator op;
} operation;

const int maxclients=50;
const int maxlenght=50;
int pinged[50];
int port;
struct Client clients[50];
struct pollfd pfd[52];
pthread_t threads[3];
int sockLocal;
int sockNet;
char *socket_path;
////////////////////////

char to_string(operator o) {
	if(o == ADD) return '+';
	if(o == SUBTRACT) return '-';
	if(o == MULTIPLY) return '*';
	if(o == DIVIDE) return '/';
	return '\0';
}

operation* parse_data(char data[1000]) {
	char num1[25];
	char num2[25];
	char op;
	int i, j;
	for(i = 0; i < strlen(data) && data[i] >= '0' && data[i] <= '9'; i++) num1[i] = data[i];
	op = data[i++];
	for(j = i; j < strlen(data); j++) num2[j - i] = data[j];
	num2[j - i - 1] = num1[i - 1] = '\0';
	
	operation* o = malloc(sizeof(operation));
	o -> arg1 = atoi(num1);
	o -> arg2 = atoi(num2);
	if(op == '+') o -> op = ADD;
	else if(op == '-') o -> op = SUBTRACT;
	else if(op == '*') o -> op = MULTIPLY;
	else if(op == '/') o -> op = DIVIDE;
	return o;
}

int random_client() {
	int t[maxclients];
	int id = 0;
	for(int i = 0; i < maxclients; i++) {
		if(clients[i].fd > 0) t[id++] = i;
	}
	if(id == 0) return -1;
	return t[rand() % id];
}

int get_empty() {
	for(int i = 0; i < maxclients; i++) 
		if(clients[i].fd <= 0) return i;
	return -1;
}
///////////////////////
void handle_result(operation o) {
	if(o.op == ADD || o.op == SUBTRACT || o.op == DIVIDE || o.op == MULTIPLY) {
		printf("%d%c%d=%d (calculated by client %s)\n", o.arg1, to_string(o.op), o.arg2, o.arg3, o.name);
	}
	else if(o.op == PING) {
		int i;
		for(i = 0; i < maxclients; i++) {
			if(strcmp(clients[i].name, o.name) == 0) {
				break;
			}
		}
		pinged[i] = 0;
	}
	else if(o.op == EXIT) {
		int i;
		for(i = 0; i < maxclients; i++) {
			if(strcmp(clients[i].name, o.name) == 0) {
				break;
			}
		}
		shutdown(pfd[i].fd, SHUT_RDWR);
	}
}

void *listener(void * arg){
listen(sockLocal, maxclients);
listen(sockNet, maxclients);
	int f;
	operation o;
	char buf[1024];
	while(1) {
		for(int i = 0; i < maxclients; i++) pfd[i].events = POLLIN;
		poll(pfd, maxclients + 2, -1);  // czeka na event
		for(int i = 0; i < maxclients; i++) {
			if((pfd[i].revents & (POLLRDHUP | POLLHUP)) != 0) {
				pfd[i].fd = -1;
				clients[i].fd = -1;
				strcpy(clients[i].name, "");
				pinged[i] = 0;
			}
			else if ((pfd[i].revents & POLLIN) != 0) {
				read(pfd[i].fd, buf, sizeof(operation));
				handle_result(*(operation*)buf);
			}
		}
		while((f = accept(pfd[maxclients].fd, NULL, NULL)) > 0) {
			read(f, buf, sizeof(operation));
			o = *(operation*)buf;
			int id = get_empty();
			for(int i = 0; i < maxclients; i++) {
				if(clients[i].fd > 0 && strcmp(clients[i].name, o.name) == 0) {
					id = -1;
				}
			}
			if(id < 0) {
				o.op = DENY;
				write(f, (void*)&o, sizeof(operation));
				shutdown(f, SHUT_RDWR);
				close(f);
				break;
			} 
			o.op = ACCEPT;
			write(f, (void*)&o, sizeof(operation));
			pfd[id].fd = f;
			strcpy(clients[id].name, o.name);
			clients[id].fd = f;
		}
		
	}
	return (void*)NULL;
}

void *ping(void * arg){
operation op;
	op.op = PING;
	while(1) {
		for(int i = 0; i < maxclients; i++) {
			if(clients[i].fd > 0) {
				if(pinged[i] == 1) {
					printf("Client %s did not respond to ping. Connection closed.\n", clients[i].name);
					shutdown(clients[i].fd, SHUT_RDWR);
					close(clients[i].fd);
					clients[i].fd = -1;
					strcpy(clients[i].name, "");
					pfd[i].fd = -1;
					pinged[i] = 0;
					continue;
				}
				write(clients[i].fd, (void*)&op, sizeof(operation));
				pinged[i] = 1;
			}
		}
		usleep(2500000);
	}
	return (void*)NULL;
}

void *terminal(void * arg){
char buf[1000];
	operation* op;
	while(1) {
		fgets(buf, 1000, stdin);
		op = parse_data(buf);
		int id = random_client();
		if(id < 0) {
			printf("No client is connected to server.\n");
			continue;
		}
		int fd = clients[id].fd;
		write(fd, (void*)op, sizeof(operation));
		free(op);
	}
}


void exit_handle(int s) {
	shutdown(sockNet, SHUT_RD);
        shutdown(sockLocal, SHUT_RD);
        close(sockLocal);
	close(sockNet);
	exit(0);
}
///////////////////////////////////////////

       int main(int argc, char ** argv){
port = atoi(argv[1]);
socket_path = malloc(strlen(argv[2]) + 1);
strcpy(socket_path, argv[2]);

for(int i = 0; i < maxclients; i++) {
		strcpy(clients[i].name, "");
		clients[i].fd = -1;
		pfd[i].fd = -1;
		pfd[i].events = POLLRDHUP;
		pinged[i] = 0;
	}
	pfd[maxclients].events = POLLIN;
	pfd[maxclients + 1].events = POLLIN; 	

	signal(SIGINT, exit_handle);	

      sockLocal=socket(AF_UNIX, SOCK_STREAM, 0);
      sockNet=socket(AF_INET, SOCK_STREAM, 0);

       struct sockaddr_un local;

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, socket_path);
       struct sockaddr_in net_addr={AF_INET,htonl(INADDR_ANY),htonl(port)};

  bind(sockLocal, (struct sockaddr*)&local, sizeof(local));
  bind(sockNet,(const struct sockaddr *)&net_addr, sizeof(net_addr));

pthread_create(&threads[0], NULL, listener, NULL);
pthread_create(&threads[1], NULL,terminal, NULL);
pthread_create(&threads[2], NULL, ping, NULL);
for(int i = 0; i < 3; i++) pthread_join(threads[i], NULL);
       return 0;
       }

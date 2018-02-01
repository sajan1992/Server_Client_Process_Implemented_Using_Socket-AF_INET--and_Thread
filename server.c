#include"header.h"
#include"prototype.h"

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* thread(void *args);
int main()
{
	//---------------------------------------------- DECLARATION OF VARIABLES --------------------------------------------------
	int fd,ret,nfd;
	struct sockaddr_in address;
	socklen_t addrlen;
	pthread_t th;
	pthread_attr_t attr;
	//---------------------------------------------------- DECLARATION ENDS ------------------------------------------------------
	
	//---------------------------------------------------------- THREAD ------------------------------------------------------------
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_attr_init(&attr);
	//-------------------------------------------------------- THREAD ENDS ----------------------------------------------------------
	fd = socket(AF_INET,SOCK_STREAM,0);	         /*creating socket(Domain,type,protocol);*/
	address.sin_family = AF_INET;
	address.sin_port = htons(5000);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	addrlen = sizeof(struct sockaddr_in);
	ret = bind(fd,(struct sockaddr*)&address,addrlen);	/*Adding name to the socket*/
	if(ret)
	{
		perror("BIND");
		exit(-1);
	}
	listen(fd,2);
	while(1)
	{
	nfd = accept(fd,(struct sockaddr*)NULL,NULL);
	if(pthread_create(&th,&attr,thread,(void*)nfd))
	{
		perror("Thread Error:");

	}
	}
	return 0;
}

void* thread(void * args)
{
	//pthread_mutex_lock(&mutex);
	pthread_detach(pthread_self());
	int result;
	Request r1;
	int fd,con;
	socklen_t addrlen;
	struct sockaddr_in addr;
	int fd1 = (int)args;
	//----------------------------------- READING FROM CLIENT -----------------------------------------------------------/
	read(fd1,&r1,sizeof(Request));
	//----------------------------------- CREATING SOCKET STREAM FOR PC ------------------------------------------------/
	fd = socket(AF_INET,SOCK_STREAM,0);	         /*creating socket(Domain,type,protocol);--> for processing client*/
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrlen = sizeof(struct sockaddr_in);
	con = connect(fd,(struct sockaddr*)&addr,addrlen);
	if(con)
	{
		perror("CONNECT:");
	}
	//-------------------------------------------- SOCKET ENDS -----------------------------------------------------/
	write(fd,&r1,sizeof(Request));
	read(fd,&result,sizeof(int));
	close(fd);
	write(fd1,&result,sizeof(int));
	close(fd1);
	//pthread_mutex_unlock(&mutex);
	pthread_exit("bye");
}

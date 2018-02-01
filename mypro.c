#include"header.h"
#include"prototype.h"

void* thread(void * args);
int main()
{
	//---------------------------------------------- DECLARATION OF VARIABLES --------------------------------------------------
	int fd,ret,nfd,result;
	socklen_t addrlen;
	struct sockaddr_in address;
	pthread_t th;
	pthread_attr_t attr;
	//---------------------------------------------------- DECLARATION ENDS ------------------------------------------------------
	
	//------------------------------------------------- THREAD ATTRIBUTE ---------------------------------------------------------/
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_attr_init(&attr);
	//----------------------------------------------- THREAD ATTRIBUTE ENDS ---------------------------------------------------------/
	
	//----------------------------------------------- CREATION OF SOCKETS ----------------------------------------------------------/
	fd = socket(AF_INET,SOCK_STREAM,0);	         /*creating socket(Domain,type,protocol);*/
	address.sin_family = AF_INET;
	address.sin_port = htons(3000);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	addrlen = sizeof(struct sockaddr_in);
	//--------------------------------------------- CREATION OF SOCKETS ENDS ----------------------------------------------------------/
	ret = bind(fd,(struct sockaddr*)&address,addrlen);	//<-----------------------------------------------Adding name to the socket*/
	if(ret)
	{
		perror("BIND");
		exit(-1);
	}
	listen(fd,5);
	while(1)
	{
	nfd = accept(fd,(struct sockaddr*)NULL,NULL);
	if(pthread_create(&th,&attr,thread,(void*)nfd))
	{
		perror("Thread Error");
	}
	}
	return 0;
}
void* thread(void * args)
{	
	pthread_detach(pthread_self());
	Request r1;
	int result;
	int nfd = (int)args;
	read(nfd,&r1,sizeof(Request));
	switch(r1.c)
	{
		case '+':
			result = r1.a + r1.b;
			break;
		case '-':
			result = r1.a - r1.b;
			break;
		case '*':
			result = r1.a * r1.b;
			break;
		case '/':
			result = r1.a / r1.b;
			break;
	}
	write(nfd,&result,sizeof(int));
	close(nfd);
	pthread_exit("bye");
}

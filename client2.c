#include"header.h"
#include"prototype.h"
int main()
{
	Request r1;
	int fd,con,nfd,result;
	struct sockaddr_in address;
	socklen_t addrlen;
	r1.a = 3;
	r1.b = 2;
	r1.c = '-';
	fd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_port = htons(5000);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrlen = sizeof(struct sockaddr_in);
	con = connect(fd,(struct sockaddr*)&address,addrlen);
	if(con)
	{
		perror("CONNECT");
		exit(-1);
	}
	
	write(fd,&r1,sizeof(Request));
	printf("Send data = %d , %d , %c\n",r1.a,r1.b,r1.c);
	read(fd,&result,sizeof(int));
	close(fd);
	printf("Recieved data (SUB)= %d\n",result);
	exit(0);
}

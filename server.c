#include<sys/select.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

struct sockaddr_in serv;
struct sockaddr_in cli;
struct timeval a;

int main()
{
	fd_set fdset,rdset;
	int csfd;
	int i=0;
	int dsfd,size;
	char buf[20];

	csfd=socket(AF_INET,SOCK_STREAM,0);
	serv.sin_family=AF_INET;
	serv.sin_port=htons(3007);
	serv.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(csfd,(struct sockaddr*)&serv,sizeof(struct sockaddr_in));

	listen(csfd,6);
	
	//for(;;)
	//{
	
	FD_SET(csfd,&fdset);
	
	a.tv_sec=5;
	a.tv_usec=0;
	rdset=fdset;
	
	select(FD_SETSIZE,&rdset,NULL,NULL,&a);
	
	
	
	for(i=0;i<FD_SETSIZE;i++)
	{
		if(FD_ISSET(i,&rdset))
		{
			printf("selected fd %d\n",i);
			if(i==csfd)
			{
				dsfd=accept(i,(struct sockaddr*)&cli,&size);
				FD_SET(dsfd,&fdset);
			}
			else
			{
				recv(i,buf,9,0);
				printf("msg=%s\n",buf);
				send(i,"Msg Rcvd",9,0);
			}
		}
	}
	//}
}

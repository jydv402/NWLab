#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>

void main()
{
	int sockfd;
	char buff[100];
	
	struct sockaddr_in server,client;
	sockfd= socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family = AF_INET;
	server.sin_port = 1234;
	server.sin_addr.s_addr = INADDR_ANY;
	
	connect(sockfd,(struct sockaddr *)&server,sizeof(server));
	
	printf("\nData received from Server : ");
	recv(sockfd,buff,100,0);
	printf("%s",buff);
	
	printf("\nEnter the data for the Server : ");
	scanf("%s",buff);
	send(sockfd,buff,100,0);
	
	close(sockfd);
}

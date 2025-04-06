#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>

void main()
{
	int sockfd, newsock;
	char buff[100];
	
	struct sockaddr_in server,client;
	sockfd= socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family = AF_INET;
	server.sin_port = 1234;
	server.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	
	if(listen(sockfd,1) == 0)
		printf("\nServer is listening\n");
	else
		printf("\nERROR\n");
		
	int len = sizeof(struct sockaddr_in);
	newsock = accept(sockfd,(struct sockaddr *)&client,(&len));
	
	printf("\nEnter the data for the Client : ");
	scanf("%s",buff);
	send(newsock,buff,100,0);
	
	printf("\nIs the word a Palindrome? : ");
	recv(newsock,buff,100,0);
	printf("\n%s\n",buff);
	
	close(sockfd);
	close(newsock);
}

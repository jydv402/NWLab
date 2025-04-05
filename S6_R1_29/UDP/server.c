#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>

int main()
{
	int sockfd,len;
	char buff[100];
	
	struct sockaddr_in server,client;
	sockfd= socket(AF_INET,SOCK_DGRAM,0);
	
	
	server.sin_family = AF_INET;
	server.sin_port = 1234;
	server.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	
	len = sizeof(client);
	
	printf("\nData received from Client : ");
	recvfrom(sockfd,buff,100,0,(struct sockaddr *)&client,&len);
	printf("%s",buff);
	
	printf("\nEnter the data for the Client : ");
	scanf("%s",buff);
	sendto(sockfd,buff,100,0,(struct sockaddr *)&client,len);
	
	printf("\n");
	
	close(sockfd);
	
	return 0;
}

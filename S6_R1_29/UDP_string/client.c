//String-Client

#include <stdio.h>
#include <unistd.h>
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
	
	len = sizeof(server);
	
	printf("\nEnter the  for the Server : ");
	scanf("%s",buff);
	sendto(sockfd,buff,100,0,(struct sockaddr *)&server,len);
	
	printf("\nData received from Server : ");
	recvfrom(sockfd,buff,100,0,(struct sockaddr *)&server,&len);
	printf("%s",buff);
	
	printf("\n");
	
	close(sockfd);
	
	return 0;
}

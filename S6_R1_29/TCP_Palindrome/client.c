#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>
#include <string.h>

void main()
{
	int sockfd,flag = 0;
	char buff[100],yes[] = "YES", no[] = "NO";
	
	struct sockaddr_in server,client;
	sockfd= socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family = AF_INET;
	server.sin_port = 1234;
	server.sin_addr.s_addr = INADDR_ANY;
	
	connect(sockfd,(struct sockaddr *)&server,sizeof(server));
	
	printf("\nData received from Server : ");
	recv(sockfd,buff,100,0);
	printf("%s",buff);
	printf("\nChecking if the word is a palindrome...\n");
	
	int len = strlen(buff);
	for(int i = 0; i < len/2;i++)
	{
		if(buff[i] != buff[len-i-1])
		{
			flag = 1;
		}
	}
	
	flag == 0 ?send(sockfd,yes,4,0):send(sockfd,no,4,0);
	
	close(sockfd);
}

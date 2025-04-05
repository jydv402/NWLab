//S6R1-29
#include<stdio.h>
#include<sys/socket.h>
#include<stddef.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
void main()
{
    
	int sockfd,vowels=0,consonants=0,words=1,lines=0;
	char buf[100];
	struct sockaddr_in server,client;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=1234;
	
	
	int len=sizeof(struct sockaddr_in);
	
        printf("\nEnter the data to send to server:");
	scanf("%99[^\n]",buf);
	sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&server,len);
	
	printf("Data received from the server:\n");
	recvfrom(sockfd,&vowels,sizeof(vowels),0,(struct sockaddr*)&server,(&len));
	printf("Count of vowels is %d\n",vowels);
	recvfrom(sockfd,&words,sizeof(words),0,(struct sockaddr*)&server,(&len));
	printf("Count of words is %d\n",words);
	recvfrom(sockfd,&lines,sizeof(lines),0,(struct sockaddr*)&server,(&len));
	printf("Count of lines is %d\n",lines);
	recvfrom(sockfd,&consonants,sizeof(consonants),0,(struct sockaddr*)&server,(&len));
	printf("Count of consonants is %d\n",consonants);
	
	
	close(sockfd);
	printf("\n");
	
}
	


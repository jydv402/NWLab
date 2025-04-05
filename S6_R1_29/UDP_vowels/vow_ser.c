//S6R1-29
#include<stdio.h>
#include<sys/socket.h>
#include<stddef.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    
	int sockfd,vowels=0,consonants=0,words=1,lines=0,i;
	char buf[100],ch;
	struct sockaddr_in server,client;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=1234;
	
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	printf("--waiting for client--");
	
	int len=sizeof(struct sockaddr_in);
	
	
	printf("\nData received from client:");
	recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client,(&len));
	printf("%s",buf);
        for(i=0;buf[i]!='\0';i++)
         {
           ch=buf[i];
           if((ch=='A')||(ch=='a')||(ch=='E')||(ch=='e')||(ch=='I')||(ch=='i')||(ch=='O')||(ch=='o')||(ch=='U')||(ch=='u'))
            {
             vowels++;
            }
           else if(ch==' ')
            {
             words++;
            }
           else if(ch=='.')
            {
             lines++;
            }
           else if(ch=='\n')
            {
             continue;
            }
           else
            {
             consonants++;
            }
        }
        sendto(sockfd,&vowels,sizeof(vowels),0,(struct sockaddr*)&client,sizeof(client));
        sendto(sockfd,&words,sizeof(words),0,(struct sockaddr*)&client,sizeof(client));
        sendto(sockfd,&lines,sizeof(lines),0,(struct sockaddr*)&client,sizeof(client));
        sendto(sockfd,&consonants,sizeof(consonants),0,(struct sockaddr*)&client,sizeof(client));
	 
	close(sockfd);
	printf("\n");
	
	}



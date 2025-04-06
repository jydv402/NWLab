//Time-Client1

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
void main()
{
  printf("Client1\n");
  char buf[50];
  int sockfd;
   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   struct sockaddr_in addr;
   addr.sin_family=AF_INET;
   addr.sin_addr.s_addr=INADDR_ANY;
   addr.sin_port=1234;
   int s=sizeof(struct sockaddr_in);
   do
    {
      printf("Enter message to server:");
      scanf("%s",buf);
      if(strcmp(buf,"stop")==0)
      break;
      sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&addr,s);
      recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&addr,&s);
      printf("Message received from server:\n   %s\n",buf);
    }
   while(strcmp(buf,"stop")!=0);
   close(sockfd);
 }

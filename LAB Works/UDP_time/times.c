//Time-Server

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
void main()
 {
   printf("Server side\n");
   int sockfd;
   char buf[50];
   struct sockaddr_in addr,addr1;
   addr.sin_family=AF_INET;
   addr.sin_addr.s_addr=INADDR_ANY;
   addr.sin_port=1234;
   int s=sizeof(struct sockaddr_in);
   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
   printf("Connection Established\n");
   do
    {
      recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&addr1,&s);
      printf("Message from client:%s\n",buf);
      pid_t pid=fork();
      if(pid==0)
       {
         struct tm*timeinfo;
         time_t rawtime;
         time(&rawtime);
         timeinfo=localtime(&rawtime);
         sprintf(buf,"Time is %d:%d:%d",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
         sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&addr1,s);
         printf("time is sent to client\n");
       }
    }
    while(strcmp(buf,"stop")!=0);
    close(sockfd);
 }   

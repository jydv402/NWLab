#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
int main()
{
        int sockfd;
        char buf[100];
        struct sockaddr_in server, client;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        server.sin_family = AF_INET;
        server.sin_port = 1234;
        server.sin_addr.s_addr = INADDR_ANY;
        int size = sizeof(struct sockaddr_in); //
        bind(sockfd, (struct sockaddr *)&server, sizeof(server));
        printf("::Connection Established::\n");
        do
        {
                recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &size);
                printf("Message from the client = %s \n", buf);
                pid_t pid = fork();
                if (pid == 0)
                {
                        struct tm *timestruct;
                        time_t rawtime;
                        time(&rawtime);
                        timestruct = localtime(&rawtime);
                        printf("Current local time : %d:%d:%d\n", timestruct->tm_hour, timestruct->tm_min, timestruct->tm_sec);
                        sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client, size);
                        printf("time is sent to client\n");
                }
        } while (strcmp(buf, "stop") != 0);
        close(sockfd);
}

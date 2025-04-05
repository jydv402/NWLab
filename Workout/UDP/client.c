#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stddef.h>

void main()
{
    int sockfd;
    char buff[100];

    struct sockaddr_in s, c;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    s.sin_family = AF_INET;
    s.sin_addr.s_addr = INADDR_ANY;
    s.sin_port = 1234;

    int len = sizeof(s);

    printf("\nData : ");
    scanf("%s", buff);
    sendto(sockfd, buff, 100, 0, (struct sockaddr *)&s, len);
    recvfrom(sockfd, buff, 100, 0, (struct sockaddr *)&s, &len);
    printf("\nRECV : %s", buff);

    close(sockfd);
}
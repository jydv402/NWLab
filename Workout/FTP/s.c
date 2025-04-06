#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stddef.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

void main()
{
    // Define the variables
    int sockfd, newsock;
    char buff[100], filename[30];
    struct sockaddr_in ser, cli;
    FILE *f1;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Define the struct
    ser.sin_family = AF_INET;
    ser.sin_port = 1234;
    ser.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
    bind(sockfd, (struct sockaddr *)&ser, sizeof(ser));

    // Listen
    listen(sockfd, 1) ? printf("Success") : printf("Error");

    // Connect
    newsock = accept(sockfd, (struct sockaddr *)&ser, sizeof(ser));

    int n = recv(newsock, filename, 30, 0);
    filename[n] = '\0';

    // Open the file
    f1 = fopen(filename, "r");

    // Send the file
    while (fgets(buff, 100, f1) != NULL)
    {
        send(newsock, buff, 100, 0);
    }
}

// Collect and send student data
// Uses UDP

#include <stdio.h>

// For the network
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

void main()
{
    // define the variables
    int sockfd, i = 0;
    struct sockaddr_in ser, cli;

    // Student details vars
    char name[30];
    int roll;
    char class[10];
    int marks[5];

    int avg;

    // Create the socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Define the struct
    ser.sin_family = AF_INET;
    ser.sin_port = 1234;
    ser.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
    bind(sockfd, (struct sockaddr *)&ser, sizeof(ser));

    // receive details from the server
    int len = sizeof(cli);
    recvfrom(sockfd, name, 30, 0, (struct sockaddr *)&cli, &len);
    recvfrom(sockfd, &roll, 1, 0, (struct sockaddr *)&cli, &len);
    recvfrom(sockfd, class, 10, 0, (struct sockaddr *)&cli, &len);
    for (int i = 0; i < 5; i++)
    {
        // receive each mark
        recvfrom(sockfd, &marks[i], 1, 0, (struct sockaddr *)&cli, &len);
    }

    // Print  Name  Roll    Class   Marks
    printf("%s\n%d\n%s\n", name, roll, class);
    while (i < 5)
    {
        printf("\t%d", marks[i]);
        // Calculate sum
        avg += marks[i];
        i++;
    }

    // Find avg
    avg = avg / 5;

    // RCV data
    sendto(sockfd, &avg, 1, 0, (struct sockaddr *)&cli, len);
}
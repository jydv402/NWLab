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

    // Get details
    printf("\nName : ");
    fgets(name, 30, stdin);

    printf("\nRoll : ");
    scanf("%d", &roll);
    getchar();

    printf("\nClass : ");
    fgets(class, 10, stdin);

    printf("\nMarks of 5 subjects : \n");
    for (i = 0; i < 5; i++)
    {
        // Read each mark
        printf("%d\t", i + 1);
        scanf("%d", &marks[i]);
    }

    // Send details to the server
    int len = sizeof(ser);
    sendto(sockfd, name, 30, 0, (struct sockaddr *)&ser, len);
    sendto(sockfd, &roll, 1, 0, (struct sockaddr *)&ser, len);
    sendto(sockfd, class, 10, 0, (struct sockaddr *)&ser, len);
    for (int i = 0; i < 5; i++)
    {
        // Send each mark
        sendto(sockfd, &marks[i], 1, 0, (struct sockaddr *)&ser, len);
    }

    // RCV data
    recvfrom(sockfd, &avg, 1, 0, (struct sockaddr *)&ser, &len);

    printf("Avg marks -> %d", avg);
}
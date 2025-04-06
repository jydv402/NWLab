#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
    FILE *fp;
    int sd, newsd, n, bd;
    char fileread[100], rcv[100];
    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
        printf("Can't create socket\n");
    else
        printf("Socket is created\n");

    // Set server details
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1234);  // Use htons for portability
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bd = bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (bd < 0)
        printf("Can't bind\n");
    else
        printf("Binded\n");

    listen(sd, 5);

    socklen_t clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);
    if (newsd < 0)
        printf("Can't accept\n");
    else
        printf("Accepted\n");

    // Receive file name
    n = recv(newsd, rcv, sizeof(rcv) - 1, 0);
    rcv[n] = '\0';

    fp = fopen(rcv, "r");
    if (fp == NULL) {
        send(newsd, "error", 5, 0);
        close(newsd);
        return 1;
    }

    // Send file contents
    while (fgets(fileread, sizeof(fileread), fp)) {
        if (send(newsd, fileread, strlen(fileread), 0) < 0) {
            printf("Can't send file contents\n");
        }
        sleep(1);
    }

    fclose(fp);
    close(newsd);
    close(sd);
    return 0;
}

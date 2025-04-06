/*
 * UDP Time-Server
 *
 * This program creates a UDP server that listens on port 1234.
 * When it receives a message, it forks a child process to respond with the current time.
 * The server stops when a message "stop" is received.
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void main()
{
  // Display startup message
  printf("Server side\n");

  int sockfd;
  char buf[50];

  // Define socket address structures for server and client.
  struct sockaddr_in addr, addr1;

  // Set up the server address structure.
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = 1234; // Server port

  // s holds the size of the sockaddr_in structure.
  int s = sizeof(struct sockaddr_in);

  // Create a UDP socket.
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  // Bind the socket to the specified IP and port.
  bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  printf("Connection Established\n");

  // Main loop: wait for client messages.
  do
  {
    // Receive message from client. addr1 will contain client's address.
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr1, &s);
    printf("Message from client: %s\n", buf);

    // Create a child process for handling the response.
    pid_t pid = fork();
    if (pid == 0)
    { // Child process
      struct tm *timeinfo;
      time_t rawtime;

      // Get current time.
      time(&rawtime);
      timeinfo = localtime(&rawtime);

      // Write current time into buf.
      sprintf(buf, "Time is %d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

      // Send time string back to client.
      sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr1, s);
      printf("Time is sent to client\n");
    }
  } while (strcmp(buf, "stop") != 0);

  // Close the socket when finished.
  close(sockfd);
}

// Time-Client2
// A UDP client that sends messages to a server and receives responses.

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
  // Inform the user which client is running.
  printf("Client2\n");

  // Buffer to hold messages.
  char buf[50];

  // Create a UDP socket.
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  // Setup server address structure.
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;         // IPv4 address family.
  addr.sin_addr.s_addr = INADDR_ANY; // Listen on any available interface.
  addr.sin_port = 1234;              // Server port number.

  // Main communication loop.
  do
  {
    // Prompt user to enter a message to send to the server.
    printf("Enter message to server:");
    scanf("%s", buf);

    // Check if the user wants to stop the conversation.
    if (strcmp(buf, "stop") == 0)
      break;

    // Send the message to the server.
    sendto(sockfd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&addr, sizeof(addr));

    // Prepare variable for the source address length.
    socklen_t addr_len = sizeof(addr);

    // Receive a response from the server.
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addr_len);

    // Display the received message.
    printf("Message received from server:\n   %s\n", buf);
  } while (strcmp(buf, "stop") != 0);

  // Close the socket before exiting.
  close(sockfd);
  return 0;
}

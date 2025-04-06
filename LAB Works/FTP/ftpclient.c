#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main()
{
  // File pointer for storing data received from server
  FILE *fp;

  // Socket descriptor and variable to store return value of recv()
  int csd, s;

  // Buffers to store filenames and received data
  char name[100], rcvg[100], fname[100];

  // Server address structure
  struct sockaddr_in servaddr;

  // Create a socket with IPv4 and TCP protocols
  csd = socket(AF_INET, SOCK_STREAM, 0);
  if (csd < 0)
  {
    // Print error if socket creation failed and exit the program
    printf("Error creating socket....\n");
    exit(0);
  }
  else
    printf("Socket is created\n");

  // Set server address parameters
  servaddr.sin_family = AF_INET;

  // Set port number; note that port should be in network byte order
  servaddr.sin_port = 1234;

  // Accept connections on any local network interface
  servaddr.sin_addr.s_addr = INADDR_ANY;

  // Connect to the server using the specified address
  if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    printf("Error in connection\n");
  else
    printf("Connected to the server\n");

  // Prompt user for the existing file name to request from server
  printf("Enter the existing file name\t");
  scanf("%s", name);

  // Prompt user for the new file name to save the received data
  printf("Enter the new file name\t");
  scanf("%s", fname);

  // Open the file for writing; create new file or overwrite if exists
  fp = fopen(fname, "w");
  if (fp == NULL)
  {
    // If file could not be opened, print error, close socket, and exit
    perror("Error opening file");
    close(csd);
    exit(1);
  }

  // Send the file name to the server
  send(csd, name, sizeof(name), 0);

  // Receive data from the server
  while (1)
  {
    s = recv(csd, rcvg, sizeof(rcvg), 0);

    // Break out if no data is received or connection is closed
    if (s <= 0)
      break;

    // Ensure the received data is null-terminated
    rcvg[s] = '\0';

    // Check if the server returned an error message
    if (strcmp(rcvg, "error") == 0)
      printf("File is not available\n");
    else
    {
      // Print received data to stdout and write it to the file
      fputs(rcvg, stdout);
      fprintf(fp, "%s", rcvg);
    }

    // Break out from the loop after processing the response once
    break;
  }

  // Close the file and the socket
  fclose(fp);
  close(csd);

  return 0;
}

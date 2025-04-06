#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  FILE *fp;
  int sd, newsd, ser, n, a, cli, pid, bd, port, clilen;

  char fileread[100], rcv[100];

  struct sockaddr_in servaddr, cliaddr;

  sd = socket(AF_INET, SOCK_STREAM, 0);

  if (sd < 0)
    printf("Cant create\n");
  else
    printf("Socket is created\n");

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = 1234;
  servaddr.sin_addr.s_addr = INADDR_ANY;

  a = sizeof(servaddr);
  bd = bind(sd, (struct sockaddr *)&servaddr, a);

  if (bd < 0)
    printf("Cant bind\n");
  else
    printf("Binded\n");
  listen(sd, 5);

  clilen = sizeof(cliaddr);
  newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);

  if (newsd < 0)
    printf("Cant accept\n");
  else
    printf("Accepted\n");

  n = recv(newsd, rcv, 100, 0);
  rcv[n] = '\0';
  fp = fopen(rcv, "r");

  if (fp == NULL)
  {
    send(newsd, "error", 5, 0);
    close(newsd);
  }

  else
  {
    while (fgets(fileread, sizeof(fileread), fp))
    {
      if (send(newsd, fileread, sizeof(fileread), 0) < 0)
      {
        printf("Can’t send file contents\n");
      }
      sleep(1);
    }

    return (0);
  }
}

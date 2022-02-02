#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

using namespace std;

int main(int argc, char** argv)
{
  int server_socket;
  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  };

  int connected_socket;
  struct sockaddr_in server;

  int server_size = sizeof(server);
  memset(&server, 0, sizeof(server));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons((short)8652);

  bind(server_socket, (struct sockaddr *)&server, sizeof(server));

  int backlog = 10;

  listen(server_socket, backlog);

  printf("%s \n", "Server socket set up");

  for (;;) {
    connected_socket = accept(server_socket, (struct sockaddr *)&server, (socklen_t*)&server_size);
    printf("%s \n", "Connection established");
  }
}

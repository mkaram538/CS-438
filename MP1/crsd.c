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

int server_socket;

typedef struct {
  char room_name[256];
  int port_num;
  int num_members;
  int slave_socket[MAX_MEMBER];
} room;

room room_db[MAX_ROOM];

int main(int argc, char** argv)
{
  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  };

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

int create_room(char[] room_name) {
  bool found = false;
  for (int i = 0; i < room_db.size(); i++) {
    if (strcmp(room_db[i], room_name)) {
      found = true;
    }
  }
  if (!found) {
    return 0;
  }

  int room_socket;
  if ((room_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  };

  struct sockaddr_in server;

  int server_size = sizeof(server);
  memset(&server, 0, sizeof(server));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons((short)1000);

  bind(room_socket, (struct sockaddr *)&server, sizeof(server));

  int backlog = 10;

  listen(room_socket, backlog);

  printf("%s \n", "Server socket set up");

  for (;;) {
    connected_socket = accept(room_socket, (struct sockaddr *)&server, (socklen_t*)&server_size);
    printf("%s \n", "Connection established");
  }

  room new_room = {room_name, 1000, 0, []};
  room_db.push_back(new_room);
}

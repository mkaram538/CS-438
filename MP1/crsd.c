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

void accept_requests(int connected_socket);
int create_room(char* room_name);
int join_room(char* room_name);
int delete_room(char* room_name);
char* get_name(char command[]);
char* get_action(char command[]);

typedef struct {
  char* room_name;
  int port_num;
  int num_members;
  int room_fd;
  int slave_socket[100];
} room;

room room_db[100];

int num_rooms = 0;

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
  server.sin_port = htons((short)8650);

  if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  };

  if (listen(server_socket, 10) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  };

  printf("Main : Ready for client connect() \n");

  int connected_socket = accept(server_socket, NULL, NULL);

  printf("Main : Connect() accepted %i \n", connected_socket);

  accept_requests(connected_socket);
}

void accept_requests(int connected_socket) {
  char command_buff[255] = {0};
  char name_buff[255] = {0};
  char action_buff[255] = {0};
  int result;
  char result_buff[255] = {0};

  for (;;) {
    read(connected_socket, command_buff, 255);
    strcpy(name_buff, get_name(command_buff));
    strcpy(action_buff, get_action(command_buff));

    if (strcmp(action_buff, "CREATE") == 0) {
      result = create_room(name_buff);
      sprintf(result_buff, "%d", result);
      printf("accept_requests : Create room return - %s \n", result_buff);
      send(connected_socket, result_buff, strlen(result_buff), 0);
      command_buff[0] = '\0';
    } else if (strcmp(action_buff, "JOIN") == 0) {
      result = join_room(name_buff);
      int room_index = atoi(result);
      sprintf(result_buff, "%d", room_db[room_index].port_num);
      printf("accept_requests : Join room return - %s \n", result_buff);
      send(connected_socket, result_buff, strlen(result_buff), 0);
      command_buff[0] = '\0';
    } else if (strcmp(action_buff, "DELETE") {
      result = delete_room(name_buff);
    }
  }
}

int create_room(char* room_name) {
  bool found = false;
  for (int i = 0; i < num_rooms; i++) {
    if (strcmp(room_db[i].room_name, room_name)) {
      found = true;
    }
  }
  if (found) {
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

  printf("create_room : Ready for client connect() \n");

  room new_room = {room_name, 1000, 0, room_socket};
  room_db[num_rooms] = new_room;
  num_rooms++;

  return 1000;
}

int join_room(char* room_name) {
  for (int i = 0; i < num_rooms; i++) {
    if (strcmp(room_db[i].room_name, room_name)) {
      return i;
    }
  }
  return -1;
}

int delete_room(char* room_name) {
  room room_to_delete;
  int room_index;
  bool found = false;
  for (int i = 0; i < num_rooms; i++) {
    if (strcmp(room_db[i].room_name, room_name)) {
      room_to_delete = room_db[i];
      room_index = i;
      found = true;
      break;
    }
  }
  if (!found) {
    return -1;
  }
  char warning_buffer[255] = "Warning : Room is Closing!";
  for (int i = 0; i < room_to_delete.num_members; i++) {
    send(room_to_delete.slave_socket[i], warning_buffer, 255, 0);
  }

  close(room_to_delete.room_fd);
  room empty_room = {};
  room_db[room_index] = empty_room;

  return 0;
}

char* get_name(char command[]) {
  int space_index;

  for (int i = 0; i < strlen(command); i++) {
    if (command[i] == ' ') {
      space_index = i;
      break;
    }
  }
  char* name_buff = (char*)malloc(strlen(command) - space_index);
  for (int j = space_index + 1; j < strlen(command); j++) {
    name_buff[j - space_index - 1] = command[j];
  }
  return name_buff;
}

char* get_action(char command[]) {
  int space_index;

  for (int i = 0; i < strlen(command); i++) {
    if (command[i] == ' ') {
      space_index = i;
      break;
    }
  }
  char* action_buff = (char*)malloc(space_index);
  for (int j = 0; j < space_index; j++) {
    action_buff[j] = command[j];
  }
  return action_buff;
}

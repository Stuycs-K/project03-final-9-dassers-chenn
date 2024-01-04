#include <string.h>
#include "networking.h"

void subserver_logic(int client_socket){
  // Listens for a string
  char input[BUFFER_SIZE];
  read(client_socket, input, sizeof(input));

  // Reply with the rot13 of the string
  for (int i = 0; i < strlen(input); i++) {
    if (input[i] - 13 < 'a') input[i] += 13;
    else input[i] -= 13;
  }

  printf("sending %s\n", input);
  write(client_socket, input, sizeof(input));

}

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup(); 

  while (1) {
    int client_socket = server_tcp_handshake(listen_socket);

    pid_t f = fork();
    if (f == 0) {
      subserver_logic(client_socket);
      exit(0);
    }
    else {
      close(client_socket);
    }
  }

}

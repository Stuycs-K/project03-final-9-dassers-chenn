#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "networking.h"

void clientLogic(int server_socket){
  // Prompts the user for a string
  char input[BUFFER_SIZE];
  printf("Enter input: ");
  fgets(input, sizeof(input), stdin);

  // Send the user input to the client.
  write(server_socket, input, sizeof(input));
  
  // Read the modified string from the server
  read(server_socket, input, sizeof(input));
  
  // prints the modified string
  printf("Modified: %s\n", input);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  
  
  while(1){
  int server_socket = client_tcp_handshake(IP);
  printf("reconnect client.\n");
  clientLogic(server_socket);
}
}

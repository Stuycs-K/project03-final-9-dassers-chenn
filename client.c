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
  printf("Message: %s\n", input);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
    printf("The current IP: %s\n", IP);


  }

  //username of client:
  char name[BUFFER_SIZE] = "";
  printf("Please input your preferred username:\n");
  fgets(name, sizeof(name), stdin);

  struct client_sockets* client = malloc(sizeof(struct client_sockets));
  name[strlen(name)-1]=0; //clear newline
  strcpy(client->username, name);

  struct client_sockets* messaging_client = malloc(sizeof(struct client_sockets));
  
    while(1){
        int server_socket = client_tcp_handshake(IP);
        fd_set read_fds;
        char buff[BUFFER_SIZE] = "";

        while (1) {
            FD_ZERO(&read_fds);
            FD_SET(STDIN_FILENO, &read_fds);
            FD_SET(server_socket, &read_fds);

            select(server_socket + 1, &read_fds, NULL, NULL, NULL);

            // if standard in, use fgets
            if (FD_ISSET(STDIN_FILENO, &read_fds)) {
                fgets(buff, sizeof(buff), stdin);
                buff[strlen(buff)-1]=0; //clear newline
                if(buff[strlen(buff)-1]==13){
                    //clear windows line ending
                    buff[strlen(buff)-1]=0;
                }
                
                strcpy(client->message, buff);
                write(server_socket, client, sizeof(struct client_sockets));
            }

            if (FD_ISSET(server_socket, &read_fds)) {
                int bytes = read(server_socket, messaging_client, sizeof(struct client_sockets));
                if (bytes == 0) {
                  printf("CLOSED SERVER SOCKET\n");
                  close(server_socket);
                }
                printf("%s's message: %s\n", messaging_client->username, messaging_client->message);
            }
        }
    }
}

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
  
    while(1){
        // int server_socket = client_tcp_handshake(IP);
        // printf("reconnect client.\n");
        // clientLogic(server_socket); // use different socket for each client
        // close(server_socket);



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
                write(server_socket, buff, sizeof(buff));
            }

            if (FD_ISSET(server_socket, &read_fds)) {
                printf("reading from server...\n");
                int bytes = read(server_socket, buff, sizeof(buff));
                if (bytes == 0) {
                  printf("CLOSING SERVER SOCKET\n");
                  close(server_socket);
                }
                printf("message: %s\n", buff);
            }
        }
    }
}

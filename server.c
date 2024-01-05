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

  fd_set read_fds;
  char buff[BUFFER_SIZE] = "";

  while(1){

        struct client_socket** listen_sockets = malloc( 5 * sizeof(struct client_socket));

        for( int i = 0; i < 5; i++){
            int listen_sockets[i] = server_setup(); 

        }

        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(listen_socket,&read_fds);
        int i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);

        //if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            printf("Recieved from terminal: '%s'\n",buff);
        }

        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            //accept the connection
            int client_socket = server_tcp_handshake(listen_socket);            
            printf("Connected, waiting for data.\n");

            //read the whole buff
            read(client_socket,buff, sizeof(buff));
            //trim the string
            buff[strlen(buff)-1]=0; //clear newline
            if(buff[strlen(buff)-1]==13){
                //clear windows line ending
                buff[strlen(buff)-1]=0;
            }

            printf("\nRecieved from client '%s'\n",buff);

            //echo the message to all clients
            close(client_socket);

        }
    }

}

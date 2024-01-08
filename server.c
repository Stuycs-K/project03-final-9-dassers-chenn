#include <string.h>
#include "networking.h"

int main(int argc, char *argv[] ) { 

  fd_set read_fds;
  char buff[BUFFER_SIZE] = "";

//   struct client_sockets** listen_sockets = malloc( 5 * sizeof(struct client_sockets));
    int sockets[5];

    for(int i = 0; i < 5; i++){
        // listen_sockets[i] = malloc(sizeof(struct client_sockets));
        // listen_sockets[i] -> socket = server_setup(); 
        sockets[i] = server_setup();
    }

    while(1){

        for (int i = 0; i < 5; i++) {
            FD_ZERO(&read_fds);
            FD_SET(STDIN_FILENO, &read_fds);
            FD_SET(sockets[i],&read_fds);
            int i = select(sockets[i]+1, &read_fds, NULL, NULL, NULL);

            //if standard in, use fgets
            if (FD_ISSET(STDIN_FILENO, &read_fds)) {
                fgets(buff, sizeof(buff), stdin);
                buff[strlen(buff)-1]=0;
                printf("Recieved from terminal: '%s'\n",buff);
            }

            // if socket
            if (FD_ISSET(sockets[i], &read_fds)) {
                printf("listening\n");
                //accept the connection
                int client_socket = server_tcp_handshake(sockets[i]);            
                printf("Connected, waiting for data.\n");

                //read the whole buff
                read(client_socket, buff, sizeof(buff));
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

}

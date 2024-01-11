#include "networking.h"

#define MAX_CLIENTS 5

int main(int argc, char *argv[]) {

    int listen_socket, client_socket, max;
    fd_set read_fds;
    char buff[BUFFER_SIZE] = "";
    int sockets[MAX_CLIENTS];
    for (int i = 0; i < MAX_CLIENTS; i++) {
      sockets[i] = 0;
    }

    listen_socket = server_setup();
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket, &read_fds);

    while (1) {
        max = listen_socket;
        printf("listen socket: %d\n", listen_socket);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (sockets[i] > 0) {
                FD_SET(sockets[i], &read_fds);
                printf("still listening from %d\n", i);
            }
            if (sockets[i] > max) {
                max = sockets[i];
            }
        }
        select(max + 1, &read_fds, NULL, NULL, NULL);
        printf("SELECTED\n");

        // if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            printf("Recieved from terminal: '%s'\n",buff);
        }

        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            // accept connection
            client_socket = server_tcp_handshake(listen_socket);
            printf("Connected, waiting for data.\n");

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (sockets[i] == 0) {
                    sockets[i] = client_socket;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (FD_ISSET(sockets[i], &read_fds)) {
                int bytes = read(sockets[i], buff, sizeof(buff));
                if (bytes == 0) {
                    printf("Client %d disconnected\n", i);
                    close(sockets[i]);
                    sockets[i] = 0;
                } else {
                    printf("\nReceived from client %d: '%s'\n", i, buff);

                    // Echo the message to all clients
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        if (sockets[j] != 0 && j != i) {
                            write(sockets[j], buff, sizeof(buff));
                            printf("echoed message to client %d\n", j);
                        }
                    }
                }
            }
        }
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(listen_socket, &read_fds);
        for (int i = 0; i < strlen(buff); i++) {
            buff[i] = 0;
        }
    }
    return 0;
}

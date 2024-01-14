#include "networking.h"

#define MAX_CLIENTS 5

int main(int argc, char *argv[]) {

    int listen_socket, client_socket, max;
    fd_set read_fds;
    char buff[BUFFER_SIZE] = "";
    int sockets[MAX_CLIENTS];
    // struct client_sockets** sockets = malloc( MAX_CLIENTS * sizeof(struct client_sockets));

    struct client_sockets* client = malloc(sizeof(struct client_sockets));


    for (int i = 0; i < MAX_CLIENTS; i++) {
        sockets[i] = 0;
    }

    listen_socket = server_setup();
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket, &read_fds);

    while (1) {
        max = listen_socket;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (sockets[i] > 0) {
                FD_SET(sockets[i], &read_fds);
            }
            if (sockets[i] > max) {
                max = sockets[i];
            }
        }
        select(max + 1, &read_fds, NULL, NULL, NULL);

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
                int bytes = read(sockets[i], client, sizeof(struct client_sockets));
                if (bytes == 0) {
                    printf("%s disconnected\n", client->username);
                    close(sockets[i]);
                    sockets[i] = 0;
                } else {
                    printf("\nReceived from %s: '%s'\n", client->username, client->message);

                    // Echo the message to all clients
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        if (sockets[j] != 0 && j != i) {
                            write(sockets[j], client, sizeof(struct client_sockets));
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

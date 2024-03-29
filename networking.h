#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <time.h>
#include <stdbool.h>

#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "19230"
#define BUFFER_SIZE 1024

struct client_sockets {
    char username[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    int socket;
    time_t time;
    bool is_active;
};

void err(int i, char*message);
int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);
char* get_timestamp();
#endif

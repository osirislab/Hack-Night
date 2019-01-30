#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "threadpool.h"
#include "user.h"

#define THREAD_POOL_SIZE 50
#define PORT 8080

void *handle_connection(void* vargp) {
    int sock = *(int*) vargp;
    close(sock);
    free(vargp);
}

/* 
 * Setup server to receive connections and hand it off to handle_connection()
 * You can ignore most of this code.
 */
void setup_serv(int port) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, 
                                                               sizeof(opt))) {
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0) {
        perror("Failed to bind port");
        exit(EXIT_FAILURE);
    }


    if (listen(server_fd, 3) < 0) {
        exit(EXIT_FAILURE);
    }

    int *new_sock;
    int client_sock;
    int addrlen = sizeof(struct sockaddr_in);
    thread_pool* tp = new_thread_pool(THREAD_POOL_SIZE);

    while ( true ) {
        client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_sock < 0) {
            puts("Error in accepting socket");
            continue;
        }

        new_sock = malloc(sizeof(int*));
        *new_sock = client_sock;

        dispatch(tp, handle_connection, (void*) &new_sock);
    }

    destroy_thread_pool(tp);
}

int main(int argc, char* argv[]) {
    return 0;
}

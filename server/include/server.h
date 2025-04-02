/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H

    #include <poll.h>
    #include <stdbool.h>
    #include <linux/limits.h>
    #include <netinet/ip.h>

    #include "network/packets.h"

    #define SERVER_MAX_CLIENTS 4
    #define PACKET_BUFFER_SIZE 1024

enum connection_status {
    UNKNOWN,
    PENDING_HELLO,
    CONNECTED,
    PLAYING,
    DEAD,
    TIMEOUT,
};

typedef struct {
    int id;
    int network_fd;
    struct sockaddr_in network_sock;
    enum connection_status status;
    struct timespec physic_clock;
    float x;
    float y;
} client_t;

typedef struct {
    struct pollfd polls[SERVER_MAX_CLIENTS + 1];
    client_t *clients[SERVER_MAX_CLIENTS + 1];
    size_t size;
} poll_config_t;

typedef struct {
    int server_fd;
    unsigned short port;
    client_t clients[SERVER_MAX_CLIENTS];
    size_t connected_client_nb;
    char map_path[PATH_MAX + 1];
    bool debug;
} server_t;

typedef struct {
    packet_type_t packet_type;
    void (*handler)(client_t *client, char buff[PACKET_BUFFER_SIZE]);
} packet_handler_t;

int init_server(server_t *server);
void launch_server(server_t *server);

void update

void hello_handler(client_t *client, char buff[PACKET_BUFFER_SIZE]);

static const packet_handler_t HANDLERS[] = {
    {HELLO, hello_handler}
};
static const size_t HANDLERS_SIZE =
    sizeof(HANDLERS) / sizeof(packet_handler_t);
#endif //SERVER_H

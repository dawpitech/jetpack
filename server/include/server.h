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
    #include "../common/network/map.h"

    #define SERVER_MAX_CLIENTS 4

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
    int player_score;
    bool player_dead;
    bool on_the_floor;
    bool going_up;
    bool debug;
    bool game_ended;
    char map[MAP_ROWS][MAP_COLS];
} client_t;

typedef struct {
    struct pollfd polls[SERVER_MAX_CLIENTS + 1];
    client_t *clients[SERVER_MAX_CLIENTS + 1];
    size_t size;
} poll_config_t;

typedef struct {
    int server_fd;
    size_t num_players;
    unsigned short port;
    client_t clients[SERVER_MAX_CLIENTS];
    size_t connected_client_nb;
    char map_path[PATH_MAX + 1];
    char map[MAP_ROWS][MAP_COLS];
    bool debug;
} server_t;

typedef struct {
    packet_type_t packet_type;
    void (*handler)(client_t *client, server_t *server,
        char buff[PACKET_BUFFER_SIZE]);
} pkt_handler_t;

int init_server(server_t *server);
void launch_server(server_t *server);

void update_player(const client_t *client);
void send_map(client_t *client);
void send_player_stats(client_t *client);
void send_game_ended(server_t *server, size_t winner_id);
void send_game_started(server_t *server);

void hello_handler(client_t *client, server_t *server,
    char buff[PACKET_BUFFER_SIZE]);
void input_handler(client_t *client, server_t *server,
    char buff[PACKET_BUFFER_SIZE]);

static const pkt_handler_t HANDLERS[] = {
    {HELLO, hello_handler},
    {INPUT, input_handler},
};

static const size_t HANDLERS_SIZE = sizeof(HANDLERS) / sizeof(pkt_handler_t);
#endif //SERVER_H

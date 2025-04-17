/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** player_update.c
*/

#include "network/packets.h"
#include "server.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void hello_handler(client_t *client, server_t *server,
    char buff[PACKET_BUFFER_SIZE])
{
    const packet_generic_t packet = {.type = ACKNOWLEDGE};

    (void)buff;
    client->status = CONNECTED;
    write(client->network_fd, &packet, sizeof(packet));
    for (int y = 0; y < MAP_ROWS; ++y)
        memcpy(client->map[y], server->map[y], MAP_COLS);
    send_map(client);
}

void input_handler(client_t *client, server_t *server,
    char buff[PACKET_BUFFER_SIZE])
{
    const packet_input_t *packet_input = (packet_input_t *)buff;

    (void)server;
    if (packet_input->input == UP) {
        client->going_up = true;
    } else if (packet_input->input == NONE) {
        client->going_up = false;
    }
    update_player(client);
}

void send_player_stats(client_t *client)
{
    const packet_player_stats_t packet = {.type = PLAYER_STATS,
        .dead = client->player_dead, .score = client->player_score};

    write(client->network_fd, &packet, sizeof(packet));
}

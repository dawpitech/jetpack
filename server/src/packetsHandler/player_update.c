/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** player_update.c
*/

#include "network/packets.h"
#include "server.h"

#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
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

static void send_game_ended_internal(server_t *server,
    packet_game_ended_t *packet, size_t best_player)
{
    for (size_t j = 0; j < server->connected_client_nb; j++) {
        server->clients[j].game_ended = true;
        packet[j].winner_id = best_player;
        if (best_player == j)
            packet[j].client_won = 1;
        write(server->clients[j].network_fd, &(packet[j]), sizeof(packet[j]));
    }
}

void send_game_ended(server_t *server, size_t winner_id)
{
    packet_game_ended_t packet[server->connected_client_nb];
    int best_score = -1;
    size_t best_player = 0;

    for (size_t i = 0; i < server->connected_client_nb; i++) {
        packet[i].type = GAME_ENDED;
        if (server->clients[i].player_dead) {
            packet[i].client_won = 0;
            continue;
        }
        if (server->clients[i].player_score > best_score) {
            best_player = i;
            best_score = server->clients[i].player_score;
        }
    }
    if (winner_id != SIZE_MAX)
        best_player = winner_id;
    send_game_ended_internal(server, packet, best_player);
}

void send_game_started(server_t *server)
{
    const packet_generic_t packet = {.type = GAME_STARTED};

    for (size_t i = 0; i < server->connected_client_nb; i++) {
        if (server->clients[i].game_ended)
            continue;
        write(server->clients[i].network_fd, &packet, sizeof(packet));
    }
}

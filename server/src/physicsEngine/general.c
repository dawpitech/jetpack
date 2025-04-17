/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** general.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "network/map.h"
#include "physics.h"
#include "server.h"

static void apply_gravity(client_t *client)
{
    if (client->going_up) {
        if (client->y - 1 < 50)
            client->y = 50 - client->y;
        if (client->y - 1 >= 50)
            client->y -= 1;
    }
    if (client->y < 50)
        client->y = 50;
    if (client->y < 361)
        client->on_the_floor = false;
    if (client->y > 361) {
        client->y = 361;
        client->on_the_floor = true;
    }
    if (!client->on_the_floor && !client->going_up) {
        client->y += 1;
    }
    client->x += 1;
    update_player(client);
}

static void compute_map_winner(server_t *server, int only_check_deaths)
{
    size_t winner_id = SIZE_MAX;
    size_t nb_deaths = 0;

    for (size_t i = 0; i < server->connected_client_nb; i++) {
        if (server->clients[i].game_ended) {
            nb_deaths++;
            continue;
        }
        if (server->clients[i].player_dead)
            nb_deaths++;
        if (!server->clients[i].player_dead)
            winner_id = i;
    }
    if (nb_deaths != (server->connected_client_nb - 1))
        winner_id = SIZE_MAX;
    if (only_check_deaths && winner_id == SIZE_MAX)
        return;
    send_game_ended(server, winner_id);
}

static void check_collide_map(server_t *server, client_t *client)
{
    int tile_size = 40;
    int clamped_y = (int)(client->y / tile_size);
    int clamped_x = (int)(client->x / tile_size);

    if (clamped_x >= MAP_COLS) {
        compute_map_winner(server, 0);
        client->game_ended = true;
        return;
    }
    if (client->map[clamped_y][clamped_x] == '_')
        return;
    if (client->map[clamped_y][clamped_x] == 'e') {
        client->player_dead = true;
        compute_map_winner(server, 1);
    } else if (client->map[clamped_y][clamped_x] == 'c') {
        client->player_score++;
        client->map[clamped_y][clamped_x] = '_';
        send_map(client);
    }
    send_player_stats(client);
}

// ReSharper disable once CppJoinDeclarationAndAssignment
void compute_physics(server_t *server, client_t *client)
{
    static int game_started = 1;
    struct timespec now;
    int diff;

    if (server->connected_client_nb < 2) {
        game_started = 1;
        return;
    }
    if (game_started) {
        send_game_started(server);
        game_started = 0;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    diff = abs((int)((client->physic_clock.tv_sec - now.tv_sec)* 1e6
        + (client->physic_clock.tv_nsec - now.tv_nsec) / 1e3));
    if (diff < 50 || client->player_dead || client->game_ended)
        return;
    apply_gravity(client);
    check_collide_map(server, client);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &client->physic_clock);
}

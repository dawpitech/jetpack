/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** general.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "network/map.h"
#include "physics.h"
#include "server.h"

static void apply_gravity(const server_t *server, client_t *client)
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

static void check_collide_map(server_t *server, client_t *client)
{
    int tile_size = 40;
    int clamped_y = (int)(client->y / tile_size);
    int clamped_x = (int)(client->x / tile_size);

    if (server->map[clamped_y][clamped_x] == '_')
        return;
    if (server->map[clamped_y][clamped_x] == 'e')
        client->player_dead = true;
    if (server->map[clamped_y][clamped_x] == 'c') {
        client->player_score++;
        server->map[clamped_y][clamped_x] = '_';
        send_map(client, server);
    }
    send_player_stats(client);
}

// ReSharper disable once CppJoinDeclarationAndAssignment
void compute_physics(server_t *server, client_t *client)
{
    struct timespec now;
    double diff;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    diff = abs((client->physic_clock.tv_sec - now.tv_sec)* 1e6
        + (client->physic_clock.tv_nsec - now.tv_nsec) / 1e3);
    if (diff < 50 || client->player_dead)
        return;
    apply_gravity(server, client);
    check_collide_map(server, client);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &client->physic_clock);
}

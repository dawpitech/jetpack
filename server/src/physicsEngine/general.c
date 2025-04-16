/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** general.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "physics.h"

static void apply_gravity(const server_t *server, client_t *client)
{
    if (client->going_up) {
        if (client->y - 1 < 100)
            client->y = 100 - client->y;
        if (client->y - 1 >= 100)
            client->y -= 1;
    }
    if (client->y < 100)
        client->y = 100;
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

// ReSharper disable once CppJoinDeclarationAndAssignment
void compute_physics(const server_t *server, client_t *client)
{
    struct timespec now;
    double diff;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    diff = abs((client->physic_clock.tv_sec - now.tv_sec)* 1e6
        + (client->physic_clock.tv_nsec - now.tv_nsec) / 1e3);
    if (diff < 50)
        return;
    apply_gravity(server, client);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &client->physic_clock);
}

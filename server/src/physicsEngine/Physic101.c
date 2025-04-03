/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Physic101.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "physics.h"

static void apply_gravity(const server_t *server, client_t *client)
{
    if (client->y > 360) {
        if (!client->on_the_floor) {
            client->on_the_floor = true;
            update_player(server, client);
        }
        return;
    }
    client->on_the_floor = false;
    client->y += 10;
    update_player(server, client);
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

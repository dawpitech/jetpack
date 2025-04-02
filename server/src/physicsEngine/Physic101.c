/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Physic101.c
*/

#include <time.h>

#include "physics.h"

static void apply_gravity(client_t *client)
{
    server
}

void compute_physics(server_t *server, client_t *client)
{
    struct timespec now;
    double diff;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    diff = (client->physic_clock.tv_sec - now.tv_sec) * 1e6
        + (client->physic_clock.tv_nsec - now.tv_nsec) / 1e3;
    if (diff < 50)
        return;
    apply_gravity(client);
}

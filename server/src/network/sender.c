/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** sender.c
*/

#include <unistd.h>

#include "logger.h"
#include "server.h"
#include "network/packets.h"

void update_player(const client_t *client)
{
    const packet_player_update_t packet = {.type = PLAYER_UPDATE,
        .x = client->x, .y = client->y, .on_the_floor = client->on_the_floor};

    if (write(client->network_fd, &packet, sizeof(packet_player_update_t))
        <= 0)
        return;
    logc(client, INFO, "Update player position");
}

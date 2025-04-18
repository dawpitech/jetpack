/*
** EPITECH PROJECT, 2025
** map update
** File description:
** uwu
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "logger.h"

void send_map(client_t *client)
{
    packet_map_desc_t map_p = {.type = MAP_DESC};

    for (int y = 0; y < MAP_ROWS; ++y)
        memcpy(map_p.map[y], client->map[y], MAP_COLS);
    write(client->network_fd, &map_p, sizeof(map_p));
    logc(client, INFO, "Sent map infos");
}

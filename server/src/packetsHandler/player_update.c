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

void hello_handler(client_t *client, server_t *server,
    char buff[PACKET_BUFFER_SIZE])
{
    const packet_generic_t packet = {.type = ACKNOWLEDGE};
    const packet_map_desc_t map_p = {.type = MAP_DESC};

    (void)buff;
    memcpy((void *)map_p.map, server->map, sizeof(server->map));
    client->status = CONNECTED;
    write(client->network_fd, &packet, sizeof(packet));
    write(client->network_fd, &map_p, sizeof(map_p));
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

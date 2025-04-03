/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** player_update.c
*/

#include "server.h"

#include <unistd.h>

void hello_handler(client_t *client, char buff[PACKET_BUFFER_SIZE])
{
    const packet_generic_t packet = {.type = ACKNOWLEDGE};

    client->status = CONNECTED;
    write(client->network_fd, &packet, sizeof(packet));
}

/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** server.c
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "network/packets.h"
#include "server.h"
#include "physics.h"
#include "logger.h"

static void delete_client(server_t *server, client_t *client)
{
    if (client->network_fd > 0)
        close(client->network_fd);
    memset(client, 0, sizeof(client_t));
    server->connected_client_nb -= 1;
    logm(ERR, server, "Connection with client was closed abruptly");
}

static client_t *get_empty_client_slot(server_t *server)
{
    for (int i = 0; i < SERVER_MAX_CLIENTS; i++)
        if (server->clients[i].network_fd == 0)
            return &server->clients[i];
    return NULL;
}

static void add_to_poll(poll_config_t *poll_config,
    const int client_fd, client_t *client)
{
    poll_config->polls[poll_config->size].fd = client_fd;
    poll_config->polls[poll_config->size].events = POLLIN;
    if (client != NULL)
        poll_config->clients[poll_config->size] = client;
    poll_config->size += 1;
}

// ReSharper disable once CppJoinDeclarationAndAssignment
static void searching_new_clients(server_t *server)
{
    socklen_t client_len = sizeof(struct sockaddr_in);
    client_t *client;

    client = get_empty_client_slot(server);
    client->network_fd = accept(server->server_fd,
        (struct sockaddr*) &client->network_sock, &client_len);
    logm(INFO, server, "New connection from %s",
        inet_ntoa(client->network_sock.sin_addr));
    client->status = PENDING_HELLO;
    client->id = (int) server->connected_client_nb;
    client->x = 0;
    client->y = 200;
    client->debug = server->debug;
    server->connected_client_nb += 1;
}

// ReSharper disable once CppJoinDeclarationAndAssignment
static void compute_incoming_packet(server_t *server, client_t *client)
{
    char buff[4096] = {0};
    bool found = false;
    packet_generic_t *gpkt;
    const long bytes_read = read(client->network_fd, buff, 4096);

    logc(client, INFO, "Incoming data");
    if (bytes_read == 0 || buff[0] == '\0') {
        delete_client(server, client);
        return;
    }
    gpkt = (packet_generic_t *) &buff;
    logc(client, INFO, "Received packet type is %d", gpkt->type);
    for (size_t i = 0; i < HANDLERS_SIZE; i++) {
        if (HANDLERS[i].packet_type != gpkt->type)
            continue;
        HANDLERS[i].handler(client, server, buff);
        found = true;
    }
    if (!found)
        logc(client, ERR, "No suitable handler for packet!");
}

static void events_loop(server_t *server)
{
    poll_config_t poll_config = {0};

    add_to_poll(&poll_config, server->server_fd, NULL);
    for (int i = 0; i < SERVER_MAX_CLIENTS; i++) {
        if (server->clients[i].network_fd == 0)
            continue;
        add_to_poll(&poll_config, server->clients[i].network_fd,
            &server->clients[i]);
        compute_physics(server, &server->clients[i]);
    }
    poll(poll_config.polls, poll_config.size, 1);
    for (size_t i = 0; i < poll_config.size; i++) {
        if (poll_config.polls[i].revents == 0)
            continue;
        if (i == 0)
            searching_new_clients(server);
        else
            compute_incoming_packet(server, poll_config.clients[i]);
    }
}

// ReSharper disable once CppDFAEndlessLoop
void launch_server(server_t *server)
{
    logm(INFO, server, "Listening on 0.0.0.0:%d", server->port);
    while (true)
        events_loop(server);
}

int init_server(server_t *server)
{
    const int reuse = 1;
    struct sockaddr_in socket_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(server->port),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };

    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd == -1 || setsockopt(server->server_fd, SOL_SOCKET,
        SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
        return -1;
    if (bind(server->server_fd, (struct sockaddr*) &socket_addr,
        sizeof(socket_addr)) == -1)
        return -1;
    if (listen(server->server_fd, SERVER_MAX_CLIENTS) == -1)
        return -1;
    return 0;
}

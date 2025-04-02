/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** main.c
*/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "server.h"

static void parse_port(const char arg[], server_t *server)
{
    server->port = strtoul(arg, NULL, 10);
    for (size_t i = 0; i < strlen(arg); i++)
        if (!isdigit(arg[i]))
            server->port = 0;
    if (server->port == 0 || errno != 0) {
        fprintf(stderr, "jetpack_server: invalid port number\n");
        server->port = 1;
    }
}

static void parse_map_path(const char arg[], server_t *server)
{
    strncpy(server->map_path, arg, PATH_MAX);
}

static int parse_args(const int argc, const char *argv[],
    server_t *server)
{
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && server->port != 0)
            return fprintf(stderr,
                "jetpack_server: multiple port parameters\n"), 1;
        if (strcmp(argv[i], "-m") == 0 && server->map_path[0] != '\0')
            return fprintf(stderr,
                "jetpack_server: multiple map parameters\n"), 1;
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
            parse_port(argv[i + 1], server);
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc)
            parse_map_path(argv[i + 1], server);
        if (strcmp(argv[i], "-d") == 0)
            server->debug = true;
    }
    if (server->port == 0 || server->map_path[0] == '\0')
        return fprintf(stderr,
            "jetpack_server: not enough parameters given\n"), 1;
    return server->port == 1;
}

int main(const int argc, const char *argv[])
{
    static server_t server = {0};

    setenv("LC_ALL", "C", 1);
    if (parse_args(argc, argv, &server) != 0)
        return EXIT_FAILURE_TECH;
    if (init_server(&server) != 0)
        return fprintf(stderr, "jetpack_server: couldn't bind socket\n"),
            EXIT_FAILURE_TECH;
    launch_server(&server);
}

/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** logger.h
*/

#ifndef LOGGER_H
    #define LOGGER_H

    #include "server.h"

typedef enum {
    INFO,
    WARN,
    ERR,
} log_t;

void logc(const client_t *client, log_t type, const char *fmt, ...);
void logm(log_t type, const server_t *server, const char *fmt, ...);

#endif //LOGGER_H

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
    info,
    warn,
    err,
} log_type;

void logc(const client_t *client, log_type type,
    const server_t *server, const char *fmt, ...);
void logm(const log_type type, const server_t *server, const char *fmt, ...);

#endif //LOGGER_H

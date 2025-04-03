/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** logger.c
*/

#include <stdarg.h>
#include <stdio.h>

#include "logger.h"

static void print_log_type(const log_t type)
{
    switch (type) {
        case INFO:
            printf("[INFO] ");
            break;
        case WARN:
            printf("[WARN] ");
            break;
        case ERR:
            printf("[ERR!] ");
            break;
    }
}

void logc(const client_t *client, const log_t type, const char *fmt, ...)
{
    va_list printf_args;

    if (!client->debug)
        return;
    va_start(printf_args, fmt);
    print_log_type(type);
    printf("CLIENT(%d): ", client->id);
    vprintf(fmt, printf_args);
    printf("\n");
    va_end(printf_args);
}

void logm(const log_t type, const server_t *server, const char *fmt, ...)
{
    va_list printf_args;

    if (!server->debug)
        return;
    va_start(printf_args, fmt);
    print_log_type(type);
    vprintf(fmt, printf_args);
    printf("\n");
    va_end(printf_args);
}

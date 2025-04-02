/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** packets.h
*/

#ifndef PACKETS_H
    #define PACKETS_H

    #ifdef __cplusplus
        #include <cstdint>
    #else
        #include <stdint.h>
    #endif

typedef enum packet_type_e {
    INVALID,
    ACKNOWLEDGE,
    HELLO,
} packet_type_t;

typedef struct packet_generic_s {
    packet_type_t type;
} packet_generic_t;

#endif //PACKETS_H

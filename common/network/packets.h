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

    #define PACKET_BUFFER_SIZE 1024

typedef float float32_t;
typedef double float64_t;

typedef enum packet_type_e {
    INVALID,
    ACKNOWLEDGE,
    HELLO,
    PLAYER_UPDATE,
} packet_type_t;

typedef struct packet_generic_s {
    packet_type_t type;
} packet_generic_t;

typedef struct packet_player_update_s {
    packet_type_t type;
    float32_t x;
    float32_t y;
    int on_the_floor;
} packet_player_update_t;

#endif //PACKETS_H

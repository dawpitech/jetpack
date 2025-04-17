/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** ClientData.hpp
*/

#pragma once

#include <array>
#include <atomic>
#include <queue>

#include "network/map.h"
#include "network/packets.h"

namespace jetpack
{
    template <typename K>
    class Vector2
    {
        public:
            Vector2(K _x, K _y): x(_x), y(_y) {}

            K x;
            K y;
    };

    class ClientData
    {
        public:
            ClientData() = default;

            bool connectedToServer = false;
            bool running = true;
	    bool won = false;
	    int winner_id = -1;
            Vector2<float> playerPosition{0.f, 200.f};
            std::atomic_bool isDead = false;
            std::atomic_int score = 0;      
            bool playerOnFloor = false;
	    bool gameStarted = false;
	    bool gameEnded = false;
            std::array<std::array<std::atomic_char, MAP_COLS>, MAP_ROWS> map;
            std::queue<player_input_t> input_queue{};
    };
}

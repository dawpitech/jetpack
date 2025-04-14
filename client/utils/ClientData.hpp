/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** ClientData.hpp
*/

#pragma once

#include <queue>

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
            Vector2<float> playerPosition{0.f, 200.f};
            bool playerOnFloor = false;
            std::queue<player_input_t> input_queue{};
    };
}

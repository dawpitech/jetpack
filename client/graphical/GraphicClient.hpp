/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GraphicClient.hpp
*/

#pragma once

#include <mutex>
#include <SFML/Graphics.hpp>

#include "client/utils/ClientData.hpp"
#include "client/graphical/Player.hpp"
#include "client/graphical/Background.hpp"

namespace jetpack::graphical
{
    class GraphicalClient
    {
        public:
            GraphicalClient();
             ~GraphicalClient() = default;

            void render();
            void updateDataCache(std::mutex &mtx, ClientData &clientData);

        private:
            sf::RenderWindow _window;
            Player _player;
            Background _background;
    };
}

/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Player.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace jetpack::graphical
{
    class Player
    {
        public:
            Player();
            ~Player() = default;

            void render(sf::RenderWindow&);
            void setPos(float x, float y);
            void setOnFloor(bool);

        private:
            sf::Texture _texture;
            sf::Sprite _sprite;
            sf::Clock _asset_animation_clock;
            std::size_t _current_asset_tile;
            bool _onFloor;
    };
};

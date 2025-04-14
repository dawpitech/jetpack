/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Background.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace jetpack::graphical
{
    class Background
    {
        public:
            Background();
            ~Background() = default;

            void render(sf::RenderWindow&);
            void setPos(float x, float y);

        private:
            sf::Texture _texture;
            sf::Sprite _sprite;
    };
};

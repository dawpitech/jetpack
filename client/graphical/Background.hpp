/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Background.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
	    sf::Texture _finish_tex;
	    sf::Sprite _finish_sprite;
            sf::Sprite _sprite;
	    sf::Sprite _sprite_rep;
    };
};

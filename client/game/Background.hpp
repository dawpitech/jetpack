/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Background.hpp
*/

#ifndef BACKGROUND_HPP
    #define BACKGROUND_HPP

    #include <SFML/Graphics.hpp>

class Background
{
    public:
        Background();
        ~Background() = default;

        void render(sf::RenderWindow&);

    private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif //BACKGROUND_HPP

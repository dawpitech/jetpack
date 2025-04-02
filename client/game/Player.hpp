/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>

class Player
{
    public:
        Player();
        ~Player() = default;

        void render(sf::RenderWindow&);

    private:
        sf::Texture _texture;
        std::size_t curr_tile;
        sf::Sprite _sprite;
        sf::Clock _sprite_clock;
};
#endif //PLAYER_HPP

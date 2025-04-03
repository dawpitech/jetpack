/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Background.cpp
*/

#include "Background.hpp"

Background::Background() {
    this->_sprite.setScale(1.75, 1.75);
    this->_sprite.setPosition(0, -50);
}

void Background::render(sf::RenderWindow& window) {
    if (!this->_texture.loadFromFile("./assets/background.png"))
        throw std::exception();
    this->_sprite.setTexture(this->_texture);
    window.draw(this->_sprite);
}

/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Background.cpp
*/

#include "Background.hpp"

jetpack::graphical::Background::Background() {
    this->_sprite.setScale(1.75, 1.75);
    this->_sprite.setPosition(0, -50);
}

void jetpack::graphical::Background::render(sf::RenderWindow& window) {
    if (!this->_texture.loadFromFile("./assets/background.png"))
        throw std::exception();
    this->_sprite.setTexture(this->_texture);
    window.draw(this->_sprite);
}

void jetpack::graphical::Background::setPos(const float x, [[maybe_unused]] const float y)
{
    this->_sprite.setPosition(x, this->_sprite.getPosition().y);
}

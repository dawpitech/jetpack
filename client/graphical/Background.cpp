/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Background.cpp
*/

#include "Background.hpp"

jetpack::graphical::Background::Background() {
    this->_sprite.setScale(2.5, 1.75);
    this->_sprite.setPosition(0, -50);
    this->_sprite_rep.setScale(2.5, 1.75);
    this->_sprite_rep.setPosition(this->_sprite.getPosition().x + this->_sprite.getGlobalBounds().width, -50);
    if (!this->_finish_tex.loadFromFile("./assets/finishline.jpg"))
        throw std::exception();
    this->_finish_sprite.setTexture(this->_finish_tex);
    this->_finish_sprite.setPosition(-500, 55);
    this->_finish_sprite.setScale(0.15, 0.27);
}

void jetpack::graphical::Background::render(sf::RenderWindow& window) {
    if (!this->_texture.loadFromFile("./assets/background.png"))
        throw std::exception();
    this->_sprite.setTexture(this->_texture);
    this->_sprite_rep.setTexture(this->_texture);
    window.draw(this->_sprite_rep);
    window.draw(this->_sprite);
    window.draw(this->_finish_sprite);
}

void jetpack::graphical::Background::setPos(const float x, [[maybe_unused]] const float y)
{
    this->_sprite.setPosition(x, this->_sprite.getPosition().y);
    this->_sprite_rep.setPosition(this->_sprite.getPosition().x + this->_sprite.getGlobalBounds().width, this->_sprite_rep.getPosition().y);
    this->_finish_sprite.setPosition(this->_sprite.getPosition().x + (this->_sprite.getGlobalBounds().width - 400), this->_finish_sprite.getPosition().y);
}

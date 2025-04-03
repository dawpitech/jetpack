/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(): curr_tile(0) {
    this->_sprite.setScale(0.5, 0.5);
    this->_sprite.setPosition(0, 200);
}

void Player::render(sf::RenderWindow& window) {
    const auto pos = this->_sprite.getPosition();
    if (!this->_texture.loadFromFile("./assets/player.png",
        sf::IntRect{static_cast<int>(134 * this->curr_tile), 134 * (this->onFloor ? 0 : 1), 134, 134}))
        throw std::exception();
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(pos);
    window.draw(this->_sprite);

    if (this->_sprite_clock.getElapsedTime() >= sf::milliseconds(80)) {
        this->curr_tile = (this->curr_tile + 1) % 4;
        this->_sprite_clock.restart();
    }
}

void Player::setPos(const float x, const float y) {
    this->_sprite.setPosition(x, y);
    printf("player pos: (%f, %f)\n", x, y);
}

void Player::setOnFloor(const bool state) {
    this->onFloor = state;
}

/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "client/utils/Logger.hpp"

jetpack::graphical::Player::Player(): _current_asset_tile(0), _onFloor(false)
{
    this->_sprite.setScale(0.5, 0.5);
}

void jetpack::graphical::Player::render(sf::RenderWindow& window) {
    const auto pos = this->_sprite.getPosition();
    const sf::IntRect asset_tile{static_cast<int>
        (134 * this->_current_asset_tile),
        134 * (this->_onFloor ? 0 : 1),
        134,
        134};
    if (!this->_texture.loadFromFile("./assets/player.png", asset_tile))
        throw std::exception();
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(pos);
    window.draw(this->_sprite);

    if (this->_asset_animation_clock.getElapsedTime() >= sf::milliseconds(80)) {
        this->_current_asset_tile = (this->_current_asset_tile + 1) % 4;
        this->_asset_animation_clock.restart();
    }
}

void jetpack::graphical::Player::setPos(const float x, const float y) {
    this->_sprite.setPosition(x, y);
    Logger::get() << "[INFO] Player position set to (" << x << ", " << y << ").";
}

void jetpack::graphical::Player::setOnFloor(const bool state) {
    this->_onFloor = state;
}

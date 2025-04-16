/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cstdlib>
#include <exception>
#include <string>
#include <array>
#include "client/utils/Logger.hpp"
#include "network/map.h"

jetpack::graphical::Player::Player(): _current_asset_tile(0), _coins_current_asset_tile(0),
    _zapper_current_asset_tile(0), _onFloor(false)
{
    this->isDead = false;
    this->_font.loadFromFile("assets/comicsans.ttf");
    this->_score_text.setFont(this->_font);
    this->_score_text.setCharacterSize(20);
    this->_sprite.setScale(0.3f, 0.3f);
    this->score = 0;
}

void jetpack::graphical::Player::render(sf::RenderWindow& window) {
    int asset_row = this->_onFloor ? 0 : 1;
    int tile_size = 40;
    if (this->isDead)
        asset_row = 3;
    auto pos = this->_sprite.getPosition();
    const sf::IntRect asset_tile{static_cast<int>
        (134 * this->_current_asset_tile),
        134 * asset_row,
        134,
        134};
    const sf::IntRect coins_asset_tile{static_cast<int>
        (192 * this->_coins_current_asset_tile),
        0,
        192,
        170};
    const sf::IntRect zapper_asset_tile{static_cast<int>
        (105 * this->_zapper_current_asset_tile),
        0,
        105,
        121};

    if (!this->_texture.loadFromFile("./assets/player.png", asset_tile))
        throw std::exception();
    if (!this->_coin_tex.loadFromFile("./assets/coins.png", coins_asset_tile))
        throw std::exception();
    if (!this->_zapper_tex.loadFromFile("./assets/zapper.png", zapper_asset_tile))
        throw std::exception();
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(pos);
    window.draw(this->_sprite);

    for (int y = 0; y < MAP_ROWS; ++y) {
        for (int x = 0; x < MAP_COLS; ++x) {
            if (this->map[y][x] == 'c') {
                sf::Sprite coin_;
                coin_.setScale(0.15f, 0.15f);
                coin_.setTexture(this->_coin_tex);
                coin_.setPosition(static_cast<float>((x * tile_size) - (this->realXPos)),
                                  static_cast<float>((y + 1.5f) * tile_size));
                window.draw(coin_);
            }
            if (this->map[y][x] == 'e') {
                sf::Sprite zapper_;
                zapper_.setScale(0.35f, 0.35f);
                zapper_.setTexture(this->_zapper_tex);
                zapper_.setPosition(static_cast<float>((x * tile_size) - this->realXPos),
                                    static_cast<float>((y + 1.5f) * tile_size));
                window.draw(zapper_);
            }
        }
    }

    this->_score_text.setString("Score: " + std::to_string(this->score));
    window.draw(this->_score_text);

    if (this->_asset_animation_clock.getElapsedTime() >= sf::milliseconds(80)) {
        this->_current_asset_tile = (this->_current_asset_tile + 1) % 4;
        this->_coins_current_asset_tile = (this->_coins_current_asset_tile + 1) % 6;
        this->_zapper_current_asset_tile = (this->_zapper_current_asset_tile + 1) % 4;
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

void jetpack::graphical::Player::setIsDead(const bool dead) {
    this->isDead = dead;
}

void jetpack::graphical::Player::setScore(const int _score) {
    this->score = _score;
}

void jetpack::graphical::Player::setMap(std::array<std::array<char, MAP_COLS>, MAP_ROWS> _map) {
    this->map = _map;
}

void jetpack::graphical::Player::setRealXPos(const int _pos) {
    this->realXPos = _pos;
}

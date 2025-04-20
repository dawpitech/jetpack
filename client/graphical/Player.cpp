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

jetpack::graphical::Player::Player(): _current_asset_tile(0), _coins_current_asset_tile(0), _zapper_current_asset_tile(0), _onFloor(false)
{
    this->isDead = false;
    this->lastDeadState = false;
    this->lastOnFloor = true;
    this->score = 0;
    this->lastScore = 0;

    this->_font.loadFromFile("assets/comicsans.ttf");
    this->_score_text.setFont(this->_font);
    this->_generic_text.setFont(this->_font);
    this->_generic_text.setCharacterSize(20);
    this->_score_text.setCharacterSize(20);
    this->_sprite.setScale(0.3f, 0.3f);

    if (!this->_jetpack_buf.loadFromFile("assets/jetpack.wav"))
        throw std::exception();
    this->_jetpack_snd.setBuffer(this->_jetpack_buf);
    this->_jetpack_snd.setLoop(true);

    if (!this->_coin_buf.loadFromFile("assets/coin.wav"))
        throw std::exception();
    this->_coin_snd.setBuffer(this->_coin_buf);

    if (!this->_death_buf.loadFromFile("assets/death.wav"))
       throw std::exception();
    this->_death_snd.setBuffer(this->_death_buf);
}

void jetpack::graphical::Player::render(sf::RenderWindow& window) {
    int asset_row = this->_onFloor ? 0 : 1;
    int tile_size = 40;
    int player_x_offset = 100;
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

    for (int y = 0; y < MAP_ROWS; ++y) {
        for (int x = 0; x < MAP_COLS; ++x) {
            if (this->map[y][x] == 'c') {
                sf::Sprite coin_;
                coin_.setScale(0.15f, 0.15f);
                coin_.setTexture(this->_coin_tex);
                //skibidi magic
                coin_.setPosition(static_cast<float>(((x * tile_size) - (this->realXPos)) + (player_x_offset - 2)),
                                  static_cast<float>((y + 1.5f) * tile_size));
                window.draw(coin_);
            }
            if (this->map[y][x] == 'e') {
                sf::Sprite zapper_;
                zapper_.setScale(0.35f, 0.35f);
                zapper_.setTexture(this->_zapper_tex);
                zapper_.setPosition(static_cast<float>(((x * tile_size) - this->realXPos) + player_x_offset),
                                    static_cast<float>((y + 1.5f) * tile_size));
                window.draw(zapper_);
            }
        }
    }

    this->_score_text.setString("Score: " + std::to_string(this->score));

    if (!this->gameStarted) {
        this->_generic_text.setString("Waiting for other players...");
        this->_generic_text.setPosition({(800.f / 2) - 130.f, 500.f / 2});
        window.draw(this->_generic_text);
    } else if (this->gameEnded) {
        this->_generic_text.setString(this->won ? "You won !" : "You lost :/");
        this->_generic_text.setPosition({(800.f / 2) - 50.f, 500.f / 2});
        window.draw(this->_generic_text);
        if (!this->won) {
            this->_generic_text.setString("Player " + std::to_string(this->winnerId + 1) + " won.");
            this->_generic_text.setPosition({(800.f / 2) - 60.f, (500.f / 2) + 30.f});
            window.draw(this->_generic_text);
        }
    } else {
        window.draw(this->_score_text);
        window.draw(this->_sprite);
    }

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
    if (this->lastOnFloor && !state) {
        this->_jetpack_snd.play();
    }
    else if (!this->lastOnFloor && state) {
        this->_jetpack_snd.stop();
    }
    this->lastOnFloor = state;
    this->_onFloor = state;
}

void jetpack::graphical::Player::setIsDead(const bool dead) {
    if (dead && !this->lastDeadState) {
        this->_death_snd.play();
        this->_jetpack_snd.stop();
    }
    this->lastDeadState = dead;
    this->isDead = dead;
}

void jetpack::graphical::Player::setScore(const int _score) {
    if (_score > this->lastScore) {
        this->_coin_snd.play();
    }
    this->lastScore = _score;
    this->score = _score;
}

void jetpack::graphical::Player::setMap(std::array<std::array<char, MAP_COLS>, MAP_ROWS> _map) {
    this->map = _map;
}

void jetpack::graphical::Player::setRealXPos(const int _pos) {
    this->realXPos = _pos;
}

void jetpack::graphical::Player::setGameEnded(const bool ended) {
    this->gameEnded = ended;
}

void jetpack::graphical::Player::setGameStarted(const bool started) {
    this->gameStarted = started;
}

void jetpack::graphical::Player::setWon(const bool _won) {
    this->won = _won;
}

void jetpack::graphical::Player::setWinnerId(const int winner_id) {
    this->winnerId = winner_id;
}

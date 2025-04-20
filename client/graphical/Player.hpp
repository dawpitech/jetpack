/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Player.hpp
*/

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <vector>
#include "network/map.h"

namespace jetpack::graphical
{
    class Player
    {
        public:
            Player();
            ~Player() = default;

            void render(sf::RenderWindow &);
            void setPos(float x, float y);
            void setIsDead(bool dead);
            void setScore(int _score);
            void setRealXPos(int pos);
            void setGameStarted(bool started);
            void setGameEnded(bool ended);
            void setWon(bool _won);
            void setWinnerId(int winner_id);
            void setMap(std::array<std::array<char, MAP_COLS>, MAP_ROWS> _map);
            void setOnFloor(bool);

        private:
            bool isDead;
            bool gameStarted;
            bool gameEnded;
            bool won;
            int winnerId;
            int score;
            float realXPos;
            std::array<std::array<char, MAP_COLS>, MAP_ROWS> map;
            sf::Texture _texture;
            sf::Sprite _sprite;
            sf::Text _score_text;
            sf::Text _generic_text;
            sf::Clock _asset_animation_clock;
            sf::Font _font;
            sf::Texture _zapper_tex;
            sf::Texture _coin_tex;
            std::size_t _current_asset_tile;
            std::size_t _coins_current_asset_tile;
            std::size_t _zapper_current_asset_tile;
            bool _onFloor;

            int lastScore;
            bool lastDeadState;
            bool lastOnFloor;
            sf::SoundBuffer _jetpack_buf;
            sf::SoundBuffer _coin_buf;
            sf::SoundBuffer _death_buf;
            sf::Sound _jetpack_snd;
            sf::Sound _coin_snd;
            sf::Sound _death_snd;
    };
}; // namespace jetpack::graphical

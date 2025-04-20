/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GraphicClient.cpp
*/

#include "GraphicClient.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>
#include "network/packets.h"

jetpack::graphical::GraphicalClient::GraphicalClient(const bool _debug_mode)
    : _window(sf::VideoMode(800, 500), "Jetpack sadride"), _player()
{
    this->_window.setFramerateLimit(30);
    this->m_debug = _debug_mode;
}

void jetpack::graphical::GraphicalClient::updateDataCache(std::mutex &mtx, ClientData &clientData)
{
    static bool up = false;
    std::array<std::array<char, MAP_COLS>, MAP_ROWS> rawMap;
    std::lock_guard lock(mtx);

    this->_player.setIsDead(clientData.isDead);
    for (int y = 0; y < MAP_ROWS; ++y) {
        for (int x = 0; x < MAP_COLS; ++x) {
            rawMap[y][x] = clientData.map[y][x].load(std::memory_order_relaxed);
        }
    }
    this->_player.setMap(rawMap);

    this->_player.setWon(clientData.won);
    this->_player.setWinnerId(clientData.winner_id);
    this->_player.setScore(clientData.score);
    this->_player.setGameEnded(clientData.gameEnded);
    this->_player.setGameStarted(clientData.gameStarted);
    this->_player.setPos(100, clientData.playerPosition.y + 30);
    this->_background.setPos(-clientData.playerPosition.x, 0);
    this->_player.setRealXPos(clientData.playerPosition.x);
    this->_player.setOnFloor(clientData.playerOnFloor);

    sf::Event event{};
    while (this->_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            clientData.running = false;
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space && !up) {
                clientData.input_queue.push(UP);
                if (this->m_debug)
                    std::cout << "[TRACE] INGEST SPACE UP INPUT" << std::endl;
                up = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space && up) {
                clientData.input_queue.push(NONE);
                if (this->m_debug)
                    std::cout << "[TRACE] INGEST SPACE RELEASE INPUT" << std::endl;
                up = false;
            }
        }
    }
}

void jetpack::graphical::GraphicalClient::render()
{
    this->_window.clear();

    this->_background.render(this->_window);
    this->_player.render(this->_window);
    this->_window.display();
}

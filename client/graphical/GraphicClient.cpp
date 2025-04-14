/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GraphicClient.cpp
*/

#include "GraphicClient.hpp"

#include <iostream>

jetpack::graphical::GraphicalClient::GraphicalClient()
    : _window(sf::VideoMode(800, 500), "Jetpack sadride"), _player()
{
    this->_window.setFramerateLimit(30);
}

void jetpack::graphical::GraphicalClient::updateDataCache(std::mutex &mtx, ClientData &clientData)
{
    std::lock_guard lock(mtx);
    this->_player.setPos(0, clientData.playerPosition.y);
    this->_background.setPos(-clientData.playerPosition.x, 0);
    this->_player.setOnFloor(clientData.playerOnFloor);

    sf::Event event{};
    while (this->_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            clientData.running = false;
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Space) {
                clientData.input_queue.push(UP);
                std::cout << "INGEST SPACE INPUT" << std::endl;
            }

    }
}

void jetpack::graphical::GraphicalClient::render()
{
    std::cout << "render" << std::endl;
    this->_window.clear();

    this->_background.render(this->_window);
    this->_player.render(this->_window);
    this->_window.display();
}

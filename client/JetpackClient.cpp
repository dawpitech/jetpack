/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** JetpackClient.cpp
*/

#include "JetpackClient.hpp"

void JetpackClient::initNetworkThread(const std::string& ip, unsigned short port)
{
    this->_connection = std::make_unique<ServerConnection>(ip, port);
    this->_connection->run(this->_player);
}

void JetpackClient::launch()
{
    this->_window.setFramerateLimit(30);
    while (true) {
        this->_window.clear();
        //printf("render\n");
        this->_background.render(this->_window);
        this->_player.render(this->_window);
        this->_window.display();

        sf::Event event{};
        while (this->_window.pollEvent(event))
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            }
    }
}

void JetpackClient::stopNetworkThread() {
    this->_connection->stop();
}

/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** JetpackClient.hpp
*/

#ifndef JETPACKCLIENT_HPP
    #define JETPACKCLIENT_HPP

#include "game/Player.hpp"


#include <SFML/Graphics.hpp>
#include <memory>

#include "network/Client.hpp"

class JetpackClient
{
    public:
        JetpackClient(): _window(sf::VideoMode(800, 600), "Jetpack sadride") {}
        ~JetpackClient() = default;
        void initNetworkThread(const std::string& ip, unsigned short port);
        void launch();
        void stopNetworkThread();

    private:
        std::unique_ptr<ServerConnection> _connection;
        sf::RenderWindow _window;
        Player _player;
};

#endif //JETPACKCLIENT_HPP

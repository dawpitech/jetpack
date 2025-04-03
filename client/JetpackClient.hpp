/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** JetpackClient.hpp
*/

#ifndef JETPACKCLIENT_HPP
    #define JETPACKCLIENT_HPP

#include "game/Background.hpp"
#include "game/Player.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

#include "network/Client.hpp"

class JetpackClient
{
    public:
        JetpackClient(): _window(sf::VideoMode(800, 500), "Jetpack sadride") {}
        ~JetpackClient() = default;
        void initNetworkThread(const std::string& ip, unsigned short port);
        void launch();
        void stopNetworkThread();

    private:
        std::unique_ptr<ServerConnection> _connection;
        sf::RenderWindow _window;
        Player _player;
        Background _background;
};

#endif //JETPACKCLIENT_HPP

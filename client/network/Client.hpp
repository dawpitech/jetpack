/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP
    #define CLIENT_HPP

    #include <netinet/in.h>
    #include <string>
    #include <thread>

    #include "client/game/Player.hpp"

class ServerConnection
{
    public:
        ServerConnection(const std::string &ip, unsigned short port);
        ~ServerConnection() = default;

        void run(Player&);
        void stop();

    private:
        std::atomic_bool should_run = true;
        sockaddr_in network_sock;
        int network_fd;
        std::unique_ptr<std::thread> network_thread;

        void handleNetwork(Player&) const;
};

#endif //CLIENT_HPP

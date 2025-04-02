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

class ServerConnection
{
    public:
        ServerConnection(const std::string &ip, unsigned short port);
        ~ServerConnection() = default;

        void run();
        void stop();

    private:
        std::atomic_bool should_run = true;
        sockaddr_in network_sock;
        int network_fd;
        std::unique_ptr<std::thread> network_thread;

        void handleNetwork();
};

#endif //CLIENT_HPP

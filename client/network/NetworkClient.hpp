/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** NetworkClient.hpp
*/

#pragma once

#include <string>
#include <thread>
#include <netinet/in.h>

#include "client/utils/ClientData.hpp"

namespace jetpack::network
{
    class NetworkClient
    {
        public:
            NetworkClient(const std::string &ip, const unsigned short port,
                const bool _debug_mode);
            ~NetworkClient()
            {
                this->network_thread->join();
            }

            void run(std::mutex& mtx, ClientData& clientData);
            void stop();
            void setDebugMode(bool debug);

        private:
            sockaddr_in network_sock;
            int network_fd;
            bool debug_mode;
            std::unique_ptr<std::thread> network_thread;

            void handleNetwork(std::mutex& mtx, ClientData& clientData) const;
    };
}

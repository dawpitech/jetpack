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
#include "client/utils/SafeSocket.hpp"

namespace jetpack::network
{
    class NetworkClient
    {
        public:
            NetworkClient(const std::string &ip, unsigned short port, bool _debug_mode);
            ~NetworkClient()
            {
                this->network_thread->join();
            }

            void run(std::mutex& mtx, ClientData& clientData);
            void setDebugMode(bool debug);

        private:
            sockaddr_in network_sock;
            int network_fd;
            SafeSocket com_socket;
            bool debug_mode;
            std::unique_ptr<std::thread> network_thread;

            void handleNetwork(std::mutex& mtx, ClientData& clientData) const;
    };
}

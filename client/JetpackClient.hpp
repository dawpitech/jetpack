/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** JetpackClient.hpp
*/

#ifndef JETPACKCLIENT_HPP
    #define JETPACKCLIENT_HPP

#include "graphical/GraphicClient.hpp"
#include "network/NetworkClient.hpp"
#include "utils/ClientData.hpp"

#include <mutex>

class JetpackClient
{
    public:
        JetpackClient(const std::string &ip, unsigned short port);
        ~JetpackClient() = default;

        void run();

    private:
        std::mutex clientDataMutex;
        jetpack::ClientData clientData;
        jetpack::network::NetworkClient _network;
        jetpack::graphical::GraphicalClient _graphical;
};

#endif //JETPACKCLIENT_HPP

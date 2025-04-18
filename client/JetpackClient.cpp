/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** JetpackClient.cpp
*/

#include "JetpackClient.hpp"

#include <iostream>

JetpackClient::JetpackClient(const std::string &ip, const unsigned short port,
    const bool debug_mode):
    _network(ip, port, debug_mode), _graphical(debug_mode)
{
    this->_network.run(this->clientDataMutex, this->clientData);
}

void JetpackClient::run()
{
    while (this->clientData.running) {
        this->_graphical.render();
        this->_graphical.updateDataCache(this->clientDataMutex, this->clientData);
    }
}

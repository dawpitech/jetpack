/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** JetpackClient.cpp
*/

#include "JetpackClient.hpp"

#include <iostream>

JetpackClient::JetpackClient(const std::string &ip, const unsigned short port):
    _network(ip, port)
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

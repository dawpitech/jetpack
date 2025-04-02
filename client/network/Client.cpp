/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Client.cpp
*/

#include <unistd.h>
#include <arpa/inet.h>

#include "Client.hpp"
#include "network/packets.h"

ServerConnection::ServerConnection(const std::string &ip, const unsigned short port)
    : network_sock{.sin_family = AF_INET, .sin_port = 0, .sin_addr = 0, .sin_zero = 0}, network_fd(0)
{
    this->network_sock.sin_port = htons(port);
    this->network_sock.sin_addr.s_addr = inet_addr(ip.c_str());
    this->network_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(this->network_fd, reinterpret_cast<sockaddr *>(&this->network_sock), sizeof(this->network_sock)) == 1)
        throw std::exception();
    printf("[INFO] Connected to server %s:%d\n", inet_ntoa(this->network_sock.sin_addr),
           ntohs(this->network_sock.sin_port));

    constexpr packet_generic_t packet{.type = HELLO};
    write(this->network_fd, &packet, sizeof(packet));
}

void ServerConnection::run() {
    this->network_thread = std::make_unique<std::thread>([this]() { this->handleNetwork(); });
}

void ServerConnection::handleNetwork() {
    while (true) {
        if (!this->should_run)
            return;
        printf("network thread running\n");
        sleep(1);
    }
}

void ServerConnection::stop() {
    this->should_run = false;
    this->network_thread->join();
}

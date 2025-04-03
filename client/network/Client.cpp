/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Client.cpp
*/

#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

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

void ServerConnection::run(Player& player) {
    this->network_thread = std::make_unique<std::thread>([this, &player]() { this->handleNetwork(player); });
}

void ServerConnection::handleNetwork(Player& player) const
{
    pollfd pollConfig = {
        .fd = this->network_fd,
        .events = POLLIN,
        .revents = 0,
    };
    char buff[PACKET_BUFFER_SIZE] = {0};

    while (true) {
        poll(&pollConfig, 1, -1);
        if (!this->should_run)
            return;
        printf("network stack up\n");
        const long bytes_r = read(this->network_fd, buff, PACKET_BUFFER_SIZE);
        if (bytes_r == 0 || buff[0] == '\0')
            return;
        switch (reinterpret_cast<packet_generic_t*>(&buff)->type)
        {
            case PLAYER_UPDATE:
            {
                const auto packet = reinterpret_cast<packet_player_update_t*>(&buff);
                player.setPos(packet->x, packet->y);
                player.setOnFloor(packet->on_the_floor);
                break;
            }
            default:
                break;
        }
    }
}

void ServerConnection::stop() {
    this->should_run = false;
    this->network_thread->join();
}

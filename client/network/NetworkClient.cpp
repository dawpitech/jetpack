/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Client.cpp
*/

#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "NetworkClient.hpp"
#include "client/utils/ClientData.hpp"
#include "client/utils/Logger.hpp"
#include "network/packets.h"

jetpack::network::NetworkClient::NetworkClient(const std::string &ip, const unsigned short port)
    : network_sock{.sin_family = AF_INET, .sin_port = 0, .sin_addr = 0, .sin_zero = 0}, network_fd(0)
{
    this->network_sock.sin_port = htons(port);
    this->network_sock.sin_addr.s_addr = inet_addr(ip.c_str());
    this->network_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(this->network_fd, reinterpret_cast<sockaddr *>(&this->network_sock), sizeof(this->network_sock)) == 1)
        throw std::exception();
    Logger::get() << "[INFO] Connected to server " << inet_ntoa(this->network_sock.sin_addr) << ":" << ntohs(this->network_sock.sin_port);

    constexpr packet_generic_t packet{.type = HELLO};
    write(this->network_fd, &packet, sizeof(packet));
}

void jetpack::network::NetworkClient::run(std::mutex& mtx, ClientData& clientData) {
    this->network_thread = std::make_unique<std::thread>([this, &mtx, &clientData] { this->handleNetwork(mtx, clientData); });
}

void jetpack::network::NetworkClient::handleNetwork(std::mutex& mtx, ClientData& clientData) const
{
    pollfd pollConfig = {
        .fd = this->network_fd,
        .events = POLLIN,
        .revents = 0,
    };
    char buff[PACKET_BUFFER_SIZE] = {0};

    while (true) {
        const auto to_read = poll(&pollConfig, 1, 10);
        std::lock_guard lock(mtx);
        if (!clientData.running)
        {
            close(this->network_fd);
            return;
        }
        while (!clientData.input_queue.empty())
        {
            packet_input_t packet = {
                .type = INPUT,
                .input = UP,
            };

            write(this->network_fd, &packet, sizeof(packet_input_t));
            clientData.input_queue.pop();
            std::cout << "SEND INPUT EVENT" << std::endl;
        }
        if (!to_read)
            continue;
        const long bytes_r = read(this->network_fd, buff, PACKET_BUFFER_SIZE);
        if (bytes_r == 0 || buff[0] == '\0')
            return;
        switch (reinterpret_cast<packet_generic_t*>(&buff)->type)
        {
            case PLAYER_UPDATE:
            {
                const auto packet = reinterpret_cast<packet_player_update_t*>(&buff);
                clientData.playerPosition.x = packet->x;
                clientData.playerPosition.y = packet->y;
                clientData.playerOnFloor = packet->on_the_floor;
                break;
            }
            default:
                break;
        }
    }
}

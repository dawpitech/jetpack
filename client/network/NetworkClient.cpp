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
            player_input_t pi = clientData.input_queue.front();
            packet_input_t packet = {
                .type = INPUT,
                .input = pi,
            };

            write(this->network_fd, &packet, sizeof(packet_input_t));
            clientData.input_queue.pop();
            std::cout << "SEND INPUT EVENT" << std::endl;
        }
        if (!to_read)
            continue;
        long bytes_r = read(this->network_fd, buff, sizeof(packet_type_t));
        if (bytes_r == 0 || buff[0] == '\0')
            return;
        auto packet_type = reinterpret_cast<packet_type_t*>(&buff);
        bytes_r = read(this->network_fd, buff + sizeof(*packet_type), PACKET_SIZES[*packet_type]);
        switch (*packet_type)
        {
            case PLAYER_UPDATE:
            {
                const auto packet = reinterpret_cast<packet_player_update_t*>(&buff);
                clientData.playerPosition.x = packet->x;
                clientData.playerPosition.y = packet->y;
                clientData.playerOnFloor = packet->on_the_floor;
                break;
            }
            case PLAYER_STATS:
            {
                const auto packet = reinterpret_cast<packet_player_stats_t*>(&buff);

                clientData.score = packet->score;
                clientData.isDead = packet->dead;
                break;
            }
            case MAP_DESC:
            {
                const auto packet = reinterpret_cast<packet_map_desc_t*>(&buff);

                for (int y = 0; y < MAP_ROWS; ++y) {
                    for (int x = 0; x < MAP_COLS; ++x) {
                        clientData.map[y][x].store(packet->map[y][x], std::memory_order_relaxed);
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}

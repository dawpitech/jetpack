/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Client.cpp
*/

#include <arpa/inet.h>
#include <ostream>
#include <poll.h>
#include <unistd.h>

#include "NetworkClient.hpp"
#include "client/utils/ClientData.hpp"
#include "client/utils/Logger.hpp"
#include "network/packets.h"

jetpack::network::NetworkClient::NetworkClient(const std::string &ip, const unsigned short port,
                                               const bool _debug_mode) :
    network_sock{.sin_family = AF_INET, .sin_port = 0, .sin_addr = 0, .sin_zero = 0}, network_fd(0), com_socket(-1),
    debug_mode()
{
    this->setDebugMode(_debug_mode);
    this->network_sock.sin_port = htons(port);
    this->network_sock.sin_addr.s_addr = inet_addr(ip.c_str());
    this->network_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(this->network_fd, reinterpret_cast<sockaddr *>(&this->network_sock), sizeof(this->network_sock)) == 1)
        throw std::exception();
    this->com_socket = SafeSocket(this->network_fd);
    if (this->debug_mode)
        Logger::get() << "[INFO] Connected to server " << inet_ntoa(this->network_sock.sin_addr) << ":"
                      << ntohs(this->network_sock.sin_port);

    constexpr packet_generic_t packet{.type = HELLO};
    this->com_socket.safeWrite(&packet, sizeof(packet));
}

void jetpack::network::NetworkClient::run(std::mutex &mtx, ClientData &clientData)
{
    this->network_thread =
        std::make_unique<std::thread>([this, &mtx, &clientData] { this->handleNetwork(mtx, clientData); });
}

void jetpack::network::NetworkClient::handleNetwork(std::mutex &mtx, ClientData &clientData) const
{
    pollfd pollConfig = {
        .fd = this->network_fd,
        .events = POLLIN,
        .revents = 0,
    };
    char buff[PACKET_BUFFER_SIZE] = {0};

    while (true)
    {
        const auto to_read = poll(&pollConfig, 1, 10);
        std::lock_guard lock(mtx);
        if (!clientData.running)
        {
            close(this->network_fd);
            return;
        }
        while (!clientData.input_queue.empty())
        {
            const player_input_t pi = clientData.input_queue.front();
            packet_input_t packet = {
                .type = INPUT,
                .input = pi,
            };

            this->com_socket.safeWrite(&packet, sizeof(packet_input_t));
            clientData.input_queue.pop();
            if (this->debug_mode)
                std::cout << "[INFO] SENDING INPUT UPDATE PACKET" << std::endl;
        }
        if (!to_read)
            continue;
        if (read(this->network_fd, buff, sizeof(packet_type_t)) == 0 || buff[0] == '\0')
            return;
        const auto packet_type = reinterpret_cast<packet_type_t *>(&buff);
        this->com_socket.safeRead(buff + sizeof(*packet_type), PACKET_SIZES[*packet_type]);
        switch (*packet_type)
        {
            case PLAYER_UPDATE:
                {
                    const auto packet = reinterpret_cast<packet_player_update_t *>(&buff);
                    if (this->debug_mode)
                        std::cout << "[INFO] Received PLAYER_UPDATE packet" << std::endl;
                    clientData.playerPosition.x = packet->x;
                    clientData.playerPosition.y = packet->y;
                    clientData.playerOnFloor = packet->on_the_floor;
                    break;
                }
            case PLAYER_STATS:
                {
                    const auto packet = reinterpret_cast<packet_player_stats_t *>(&buff);

                    if (this->debug_mode)
                        std::cout << "[INFO] Received PLAYER_STATS packet" << std::endl;
                    clientData.score = packet->score;
                    clientData.isDead = packet->dead;
                    break;
                }
            case MAP_DESC:
                {
                    const auto packet = reinterpret_cast<packet_map_desc_t *>(&buff);

                    if (this->debug_mode)
                        std::cout << "[INFO] Received MAP_DESC packet" << std::endl;
                    for (int y = 0; y < MAP_ROWS; ++y)
                    {
                        for (int x = 0; x < MAP_COLS; ++x)
                        {
                            clientData.map[y][x].store(packet->map[y][x], std::memory_order_relaxed);
                        }
                    }
                    break;
                }
            case GAME_ENDED:
                {
                    const auto packet = reinterpret_cast<packet_game_ended_t *>(&buff);

                    if (this->debug_mode)
                        std::cout << "[INFO] Received GAME_ENDED packet" << std::endl;
                    clientData.won = packet->client_won != 0;
                    clientData.winner_id = packet->winner_id;
                    clientData.gameEnded = true;
                    break;
                }
            case GAME_STARTED:
                {
                    if (this->debug_mode)
                        std::cout << "[INFO] Received GAME_STARTED packet" << std::endl;
                    clientData.gameStarted = true;
                    break;
                }
            default:
                break;
        }
    }
}

void jetpack::network::NetworkClient::setDebugMode(const bool debug) { this->debug_mode = debug; }

/*
** EPITECH PROJECT, 2025
** arguments
** File description:
** uwu
*/

#include "Arguments.hpp"
#include <iostream>
#include <string>

Arguments::Arguments() {
    this->m_ip = "127.0.0.1";
    this->m_port = 1234;
}

bool Arguments::parseArguments(const int argc, const char **argv) {
    if (argc > 5) {
        this->showHelp();
        return false;
    }

    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if (arg == "-i") {
            if ((i + 1) >= argc) {
                this->showHelp();
                return false;
            }
            this->m_ip = argv[i++ + 1];
            continue;
        }
        if (arg == "-p") {
            if ((i + 1) >= argc) {
                this->showHelp();
                return false;
            }
            int port = std::stoi(argv[i++ + 1]);
            if (port < 1 || port > 65535) {
                std::cerr << "jetpack_client: port must be between 1 and 65535" << std::endl;
                return false;
            }
            this->m_port = static_cast<unsigned short>(port);
            continue;
        }
        this->showHelp();
        return false;
    }
    return true;
}

void Arguments::showHelp(void) const {
    std::cout << "Usage: ./jetpack_client [options]\n"
              << "\nOptions:\n"
              << "  -i <ip>      IP address to connect to (default: 127.0.0.1)\n"
              << "  -p <port>    Port number to use       (default: 1234)\n";
}

unsigned short Arguments::getPort(void) const {
    return this->m_port;
}

std::string Arguments::getIp(void) const {
    return this->m_ip;
}

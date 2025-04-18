/*
** EPITECH PROJECT, 2025
** arguments
** File description:
** uwu
*/

#pragma once

#include <string>

class Arguments {
public:
    Arguments();

    bool parseArguments(const int argc, const char **argv);
    unsigned short getPort(void) const;
    std::string getIp(void) const;
    bool getDebugMode(void) const;

private:
    void showHelp(void) const;
    
    unsigned short m_port;
    std::string m_ip;
    bool m_debug_mode;
};

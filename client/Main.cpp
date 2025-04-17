/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Main.cpp
*/

#include "JetpackClient.hpp"
#include "client/Arguments.hpp"
#include "utils/Logger.hpp"
#include "graphical/GraphicClient.hpp"

int main(const int argc, const char **argv)
{
    Arguments arg_parser;

    if (!arg_parser.parseArguments(argc, argv))
        return 84;

    JetpackClient client{arg_parser.getIp(), arg_parser.getPort()};
    client.run();
    return 0;
}

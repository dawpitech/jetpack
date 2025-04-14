/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Main.cpp
*/

#include "JetpackClient.hpp"
#include "utils/Logger.hpp"
#include "graphical/GraphicClient.hpp"

int main()
{
    JetpackClient client{"127.0.0.1", 1234};

    client.run();
    return 0;
}

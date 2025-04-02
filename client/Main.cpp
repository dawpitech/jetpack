/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Main.cpp
*/

#include <unistd.h>

#include "JetpackClient.hpp"

int main()
{
    JetpackClient client;

    client.initNetworkThread("127.0.0.1", 1234);
    client.launch();
    client.stopNetworkThread();
    return 0;
}

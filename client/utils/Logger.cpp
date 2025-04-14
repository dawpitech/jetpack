/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Logger.cpp
*/

#include "client/utils/Logger.hpp"

namespace jetpack
{
    Logger* Logger::_instance = nullptr;
    std::mutex Logger::_mutex;
}

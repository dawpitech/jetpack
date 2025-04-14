/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Logger.hpp
*/

#pragma once

#include <iostream>
#include <mutex>

namespace jetpack
{
    class Logger
    {
            static Logger *_instance;
            static std::mutex _mutex;
            bool _debug_mode_enabled = false;

        protected:
            Logger() = default;
            ~Logger() = default;

        public:
            Logger(Logger &other) = delete;
            void operator=(const Logger &) = delete;

            static Logger& get()
            {
                std::lock_guard lock(_mutex);
                if (_instance == nullptr)
                {
                    _instance = new Logger();
                }
                return *_instance;
            }

            void setDebug(const bool state) { this->_debug_mode_enabled = state; }

            [[nodiscard]] bool isDebugEnabled() const { return this->_debug_mode_enabled; }

            template <typename T>
            Logger& operator<<(const T& data)
            {
                if (!this->_debug_mode_enabled)
                    return *this;

                std::lock_guard lock(_mutex);
                std::cout << data << std::endl;

                return *this;
            }
    };
} // namespace jetpack

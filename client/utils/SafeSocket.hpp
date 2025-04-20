/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** SafeSocket.hpp
*/

// ReSharper disable CppDFAConstantConditions

#ifndef SAFESOCKET_HPP
    #define SAFESOCKET_HPP

    #include <iostream>

    #ifdef CAN_CLOSE
        #define CAPABILITY_TO_CLOSE 0
    #else
        #define CAPABILITY_TO_CLOSE 1
    #endif

class SafeSocket
{
    public:
        class SocketException final : std::exception
        {
            public:
                explicit SocketException(const std::string& what)
                {
                    this->_what = what;
                }

                [[nodiscard]] const char *what() const noexcept override { return this->_what.c_str(); }

            private:
                std::string _what;
        };

        explicit SafeSocket(const int fd)
        {
            this->_fd = fd;
        }
        ~SafeSocket()
        {
            if (this->_fd != -1 && this->safeToClose)
                close(this->_fd);
        }

        std::size_t safeRead(void *buffer, const std::size_t size) const
        {
            const std::size_t bytes_read = read(this->_fd, buffer, size);
            if (bytes_read <= 0 && size != 0)
                throw SocketException("Error occurred while reading a safe socket");
            return bytes_read;
        }
        std::size_t safeWrite(const void *buffer, const std::size_t size) const
        {
            const std::size_t written_bytes = write(this->_fd, buffer, size);
            if (written_bytes <= 0 && size != 0)
                throw SocketException("Error occurred while writing in a safe socket");
            return written_bytes;
        }

    private:
        int _fd = -1;
        bool safeToClose = CAPABILITY_TO_CLOSE;
};

#endif //SAFESOCKET_HPP

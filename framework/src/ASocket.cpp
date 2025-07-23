// ASocket.cpp

#include <unistd.h>         // close
#include <iostream>         // std::runtime_error

#include <sys/socket.h>         // struct sockaddr

#include "ASocket.hpp"      // ASocket

using namespace ilrd;

int ASocket::GetFD() const
{
    return m_fd;
}

ASocket::ASocket(const int fd): m_fd(fd)
{
    if (m_fd == -1)
    {
        throw std::runtime_error("failed to create socket");
    }

    int res = 0;

    if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &res,
                                                        sizeof(int)) < 0)
    {
        throw std::runtime_error("failed to reuse an existing socket");
    }
}

ASocket::ASocket(const ASocket& other) : m_fd(other.m_fd)
{ }

ASocket::~ASocket()
{
    close(m_fd);
}

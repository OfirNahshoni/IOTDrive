/*******************************************************************************
* File name: TCPConnSocket.cpp
* Owner: Ofir Nahshoni
* Review: Liad
* Review status: NOT Ready
*******************************************************************************/

#include <iostream>             // std::
#include <cstring>              // memset

#include "../include/TCPConnSocket.hpp"

using namespace ilrd;

TCPConnSocket::TCPConnSocket(): ASocket(socket(AF_INET,
                                                    SOCK_STREAM, 0))
{ }

TCPConnSocket::TCPConnSocket(const TCPConnSocket& other) : ASocket(other.GetFD())
{ }

TCPConnSocket::TCPConnSocket(int fd): ASocket(fd)
{ }

void TCPConnSocket::Connect(const std::string& listenPortNum,
                            const std::string& listenIP)
{
    struct addrinfo* p;
    struct addrinfo* servInfo;

    try
    {
        GetAddrInfo(listenIP, listenPortNum, &servInfo);
    }
    catch(const std::exception& e)
    {
        std::cerr << "failed to " << e.what() << std::endl;
        throw;
    }

    for (p = servInfo; p != NULL; p = p->ai_next)
    {
        if (connect(GetFD(), p->ai_addr, p->ai_addrlen) == -1)
        {
            continue;
        }

        break;
    }

    freeaddrinfo(servInfo);

    if (!p)
    {
        throw std::runtime_error("failed to connect socket to TCP listener");
    }
}

size_t TCPConnSocket::Send(const char* msg, size_t length)
{
    ssize_t sum = 0;

    while (sum < static_cast<ssize_t>(length))
    {
        sum += send(GetFD(), msg + sum, length - sum, 0);
    }

    return sum;
}

size_t TCPConnSocket::Receive(char* outMsg, size_t length)
{

    ssize_t sum = 0;

    while (sum < static_cast<ssize_t>(length))
    {
        sum += recv(GetFD(), outMsg + sum, length - sum, 0);
    }

    return sum;
}

void TCPConnSocket::GetAddrInfo(const std::string& ip, const std::string& port,
                                struct addrinfo** servInfo)
{
    struct addrinfo hints;
    const char* serverIP = ip.empty() ? NULL : ip.c_str();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(serverIP, port.c_str(), &hints, servInfo) != 0)
    {
        throw std::runtime_error("get server address");
    }
}

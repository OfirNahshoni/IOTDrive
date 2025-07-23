/*******************************************************************************
* File name: TCPListenerSocket.cpp
* Owner: Ofir Nahshoni
* Review: Liad
* Review status: NOT Ready
*******************************************************************************/

#include <iostream>                 // std::
#include <cstring>                  // memset

#include "TCPListenerSocket.hpp"    // TCPListenerSocket

using namespace ilrd;

TCPListenerSocket::TCPListenerSocket(const std::string& portNum, const int th):
                                    ASocket(socket(AF_INET, SOCK_STREAM, 0))
{
    int reuse = 1;
    struct addrinfo* p;
    struct addrinfo* servInfo;

    try
    {
        GetAddrInfo(portNum, &servInfo);
    }
    catch(const std::exception& e)
    {
        std::cerr << "failed to " << e.what() << '\n';
        throw;
    }

    for (p = servInfo; p != NULL; p = p->ai_next)
    {
        if (setsockopt(GetFD(), SOL_SOCKET, SO_REUSEADDR, &reuse,
                        sizeof(socklen_t)) == -1)
        {
            std::cerr << "failed in setsockopt()" << std::endl;
            continue;
        }

        if (bind(GetFD(), p->ai_addr, p->ai_addrlen) == -1)
        {
            std::cerr << "failed in bind()" << std::endl;
            continue;
        }

        if (listen(GetFD(), th) == -1)
        {
            std::cerr << "failed in listen()" << std::endl;
            continue;
        }

        break;
    }

    freeaddrinfo(servInfo);

    if (!p)
    {
        throw std::runtime_error("failed to create TCP listener socket");
    }
}

std::unique_ptr<TCPConnSocket> TCPListenerSocket::Accept()
{
    struct sockaddr addrNewConn;
    socklen_t addrLen = sizeof(addrNewConn);

    int newConnFD = accept(GetFD(), (struct sockaddr*)&addrNewConn, &addrLen);

    if (newConnFD == -1)
    {
        throw std::runtime_error("failed to accept new connection");
    }

    return std::make_unique<TCPConnSocket>(newConnFD);
}

void TCPListenerSocket::GetAddrInfo(const std::string& port,
                                    struct addrinfo** servInfo)
{
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port.c_str(), &hints, servInfo) != 0)
    {
        throw std::runtime_error("get possible addresses");
    }
}

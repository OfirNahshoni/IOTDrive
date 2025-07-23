/*******************************************************************************
* File name: UDPSocket.cpp
* Owner: Ofir Nahshoni
* Review: Liad
* Review status: Ready to CR
*******************************************************************************/

#include <iostream>         // std::cout
#include <cstring>          // std::memset

#include "UDPSocket.hpp"    // UDPSocket

using namespace ilrd;

UDPSocket::UDPSocket(const std::string& portNum, bool bindFlag) :
                ASocket(socket(AF_INET, SOCK_DGRAM, 0))
{
    struct addrinfo* p;
    struct addrinfo* servInfo;

    try
    {
        GetAddrInfo("", portNum, &servInfo);
    }
    catch (const std::exception& e)
    {
        std::cerr << "failed to " << e.what() << std::endl;
        throw;
    }

    if (bindFlag)
    {
        for (p = servInfo; p != NULL; p = p->ai_next)
        {
            if (bind(GetFD(), p->ai_addr, p->ai_addrlen) == -1)
            {
                continue;
            }

            break;
        }

        if (!p)
        {
            throw std::runtime_error("failed to bind socket with address");
        }
    }

    freeaddrinfo(servInfo);
}

void UDPSocket::SetTargetAddr(const std::string& portNum,
                                const std::string targetIP)
{
    struct addrinfo* p;

    try
    {
        GetAddrInfo(targetIP, portNum, &p);
    }
    catch(const std::exception& e)
    {
        std::cerr << "failed to " << e.what() << std::endl;
    }

    m_target_addr = *(p->ai_addr);
    freeaddrinfo(p);
}

void UDPSocket::SetBroadcast(bool broadFlag)
{
    int flag = broadFlag ? 1 : 0;

    if (setsockopt(GetFD(), SOL_SOCKET, SO_BROADCAST, &flag, sizeof(int)) < 0)
    {
        throw std::runtime_error("failed to set socket to broadcast listening");
    }
}

size_t UDPSocket::Send(const char* msg, size_t length)
{
    socklen_t aLen = sizeof(m_target_addr);
    const ssize_t bytesSent = sendto(GetFD(), msg, length, 0, &m_target_addr,
                                                                        aLen);

    if (bytesSent == -1)
    {
        throw std::runtime_error("failed to send message");
    }

    return bytesSent;
}

size_t UDPSocket::Receive(char* outMsg, size_t length)
{
    socklen_t aLen = sizeof(m_target_addr);
    // const size_t buffMaxSize = 4096;
    // char buffer[buffMaxSize];

    const ssize_t bytesReceived = recvfrom(GetFD(), outMsg, length, 0,
                                    (struct sockaddr*)&m_target_addr, &aLen);

    if (bytesReceived == -1)
    {
        throw std::runtime_error("failed to receive message");
    }

    // outMsg.assign(buffer, bytesReceived);


    return bytesReceived;
}

void UDPSocket::GetAddrInfo(std::string targetIP, const std::string& portNum,
                            struct addrinfo** servInfo)
{
    struct addrinfo hints;
    const char* t_IP = targetIP.empty() ? NULL : targetIP.c_str();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(t_IP, portNum.c_str(), &hints, servInfo) != 0)
    {
        throw std::runtime_error("get possible addresses");
    }
}

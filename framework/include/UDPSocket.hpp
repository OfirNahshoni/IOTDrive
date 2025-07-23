/**
* @file: UDPSocket.hpp
* @author: Ofir Nahshoni
* @brief: API for UDP Socket capable of sending and receiving messages
* from other UDP socket. can be used as a Server or as a Client.
*/

#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <netdb.h>              // struct addrinfo
#include <sys/socket.h>         // struct sockaddr

#include "ASocket.hpp"          // ASocket
#include "ISendableSocket.hpp"  // ISendableSocket

namespace ilrd
{

class UDPSocket: public ASocket, public ISendableSocket
{
public:
    explicit UDPSocket(const std::string& portNum, bool bindFlag = false);
    void SetTargetAddr(const std::string& portNum, const std::string targetIP);
    void SetBroadcast(bool broadFlag = false);
    size_t Send(const char* msg, size_t length);
    size_t Receive(char* outMsg, size_t length);

private:
    struct sockaddr m_target_addr;
    void GetAddrInfo(std::string targetIP, const std::string& portNum,
                    struct addrinfo** servInfo);
};  // class UDPSocket

}   // namespace ilrd

#endif  // UDP_SOCKET_H

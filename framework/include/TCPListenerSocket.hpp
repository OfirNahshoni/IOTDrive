/**
* @file: TCPListenerSocket.hpp
* @author: Ofir Nahshoni
* @brief: API for TCP Listener (server) Socket that can listen to incoming
* Clients connections - particularly TCPConnSocket objects.
*/

#ifndef TCP_LISTENER_SOCKET_H
#define TCP_LISTENER_SOCKET_H

#include <memory>               // std::unique_ptr

#include "ASocket.hpp"          // ASocket
#include "TCPConnSocket.hpp"    // TCPConnSocket

namespace ilrd
{

class TCPListenerSocket: public ASocket
{
public:
    explicit TCPListenerSocket(const std::string& portNum, const int th);
    std::unique_ptr<TCPConnSocket> Accept();

private:
    void GetAddrInfo(const std::string& port, struct addrinfo** servInfo);
};  // class TCPListenerSocket

}   // namespace ilrd

#endif  // TCP_LISTENER_SOCKET_H

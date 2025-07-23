/**
* @file: TCPConnSocket.hpp
* @author: Ofir Nahshoni
* @brief: API for TCP Connection Socket that can connect to a listener (server)
* socket, and to send and receive messages from other TCP connection sockets.
*/

#ifndef TCP_CONNECTION_SOCKET_H
#define TCP_CONNECTION_SOCKET_H

#include <netdb.h>              // struct addrinfo
#include <sys/socket.h>         // struct sockaddr

#include "ASocket.hpp"          // ASocket
#include "ISendableSocket.hpp"  // ISendableSocket

namespace ilrd
{

class TCPConnSocket: public ASocket, public ISendableSocket
{
public:
    explicit TCPConnSocket();
    TCPConnSocket(const TCPConnSocket& other);
    // TCPConnSocket& operator=(const TCPConnSocket& rhs);
    TCPConnSocket(int fd);
    void Connect(const std::string& listenPortNum, const std::string& listenIP);
    size_t Send(const char* msg, size_t length);
    size_t Receive(char* outMsg, size_t length);

private:
    void GetAddrInfo(const std::string& ip, const std::string& port,
                    struct addrinfo** servInfo);
};  // class TCPConnSocket

}   // namespace ilrd

#endif  // TCP_CONNECTION_SOCKET_H

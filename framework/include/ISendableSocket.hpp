/**
* @file: ISendableSocket.hpp
* @author: Ofir Nahshoni
* @brief: This is an interface for sockets with the ability of
* sending & receiving messages.
*/

#ifndef I_SENDABLE_SOCKET_H
#define I_SENDABLE_SOCKET_H

#include <sys/types.h>      // ssize_t
#include <string>           // std::string

namespace ilrd
{

class ISendableSocket
{
public:
    virtual size_t Send(const char* msg, size_t length) = 0;
    virtual size_t Receive(char* outMsg, size_t length) = 0;
};  // class ISendableSocket

}   // namespace ilrd

#endif     // I_SENDABLE_SOCKET_H

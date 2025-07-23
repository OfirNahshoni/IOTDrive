/**
* @file: NBDServer.cpp
* @author: Ofir Nahshoni
* @brief: This is a header that defines the API of NBDServer.
*/

#ifndef ILRD_RD1645_NBD_SERVER_HPP
#define ILRD_RD1645_NBD_SERVER_HPP

#include <cstddef>              // size_t
#include <optional>             // std::optional

#include "TCPConnSocket.hpp"

namespace ilrd
{

class NBDServer
{
public:
    NBDServer(const std::string& devicePath, size_t devSize);
    ~NBDServer();
    TCPConnSocket& GetTCPSocket();
    static uint64_t Ntohll(uint64_t a);

private:
    int m_fdDevice;
    std::optional<int> m_nbdClientSocket;
    std::optional<TCPConnSocket> m_nbdServerSocket;
    static int m_nbdToRemove;

    void NBDClient() const;
    void Init(size_t deviceSize);
    static void RemoveNBDConn(int signalNum);
};  // class NBDServer
    
}   // namespace ilrd

#endif  // ILRD_RD1645_NBD_SERVER_HPP
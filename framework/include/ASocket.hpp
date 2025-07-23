/**
* @file: ASocket.hpp
* @author: Ofir Nahshoni
* @brief: This header defines an abstract class of a Socket.
*/

#ifndef A_SOCKET_H
#define A_SOCKET_H

namespace ilrd
{

class ASocket
{
public:
    int GetFD() const;

protected:
    explicit ASocket(int fd);
    ASocket(const ASocket& other);
    virtual ~ASocket() = 0;

private:
    const int m_fd;
};  // class ASocket

}   // namesapce ilrd

#endif  // A_SOCKET_H
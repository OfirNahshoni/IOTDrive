/**
* @file: MasterProxy.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines API for MasterProxy, which is
* a class that handles the communication with the Master. it uses UDP socket,
* and implements the interface IInputProxy.
*/

#ifndef ILRD_RD1645_MASTER_PROXY_HPP
#define ILRD_RD1645_MASTER_PROXY_HPP

#include <mutex>                // std::mutex
#include <memory>               // std::shared_ptr
#include <optional>

#include "UID.hpp"
#include "UDPSocket.hpp"
#include "ITaskArgs.hpp"
#include "IInputProxy.hpp"

namespace ilrd
{

class MasterProxy : public IInputProxy
{
public:
    friend class Handleton;
    ~MasterProxy() = default;
    void Init(const std::string& port);
    int GetSocketFD() const;
    std::shared_ptr<ITaskArgs> GetTaskArgs(int fd, Mode mode);
    void SendReadMessageResponse(const UID& uid, bool status, size_t length,
        std::shared_ptr<char[]> data);
        void SendWriteMessageResponse(const UID& uid, bool status);
        
private:
    std::optional<UDPSocket> m_udpSocket;
    std::mutex m_mutex;

    MasterProxy() = default;
};  // class MasterProxy

}   // namespace ilrd

#endif  // ILRD_RD1645_MASTER_PROXY_HPP
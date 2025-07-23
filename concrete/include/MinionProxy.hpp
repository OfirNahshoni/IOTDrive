/**
* @file: MinionProxy.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the API for send and track all 
* receiving messages getting from the incoming Tickets. This class is
* responsible for creating AMessage objects, and send it by UDPSocket.
*/

#ifndef ILRD_RD1645_MINION_PROXY_HPP
#define ILRD_RD1645_MINION_PROXY_HPP

#include <mutex>                    //
#include <map>                      // std::map

#include "UID.hpp"                  // ilrd::UID
#include "UDPSocket.hpp"            // ilrd::UDPSocket
#include "IMinionProxy.hpp"         // ilrd::IMinionProxy

namespace ilrd
{

class MinionProxy : public IMinionProxy
{
public:
    MinionProxy(const std::string& portSelf, const std::string& portTarget, 
                const std::string& ipTarget);
    ~MinionProxy() = default;
    
    void AddWriteTask(size_t offset, size_t length, const UID& uid,
                std::shared_ptr<char[]> data, 
                std::function<void(const std::shared_ptr<AMessage>&)> onDone);
    void AddReadTask(size_t offset, size_t length, const UID& uid,
                std::function<void(const std::shared_ptr<AMessage>&)> onDone);
    int GetMinionFD();
    void OnMinionFDWakeup();

private:
    UDPSocket m_udp;
    std::mutex m_mutex;
    std::map<UID, std::function<void(const std::shared_ptr<AMessage>&)>> m_map;
};  // class MinionProxy

}   // namespace ilrd

#endif  // ILRD_RD1645_MINION_PROXY_HPP
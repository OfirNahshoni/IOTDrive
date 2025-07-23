/**
* @file: IMinionProxy.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the interface for communication 
* between the Minion and rest of the system: MinionManager.
*/

#ifndef ILRD_RD1645_IMINION_PROXY_HPP
#define ILRD_RD1645_IMINION_PROXY_HPP

#include <functional>               // std::function 
#include <memory>                   // std::shared_ptr

#include "AMessage.hpp"             // ilrd::AMessage
#include "DispatchCallback.hpp"     // ilrd::ACallback<Event>

namespace ilrd
{

class IMinionProxy
{
public:
    virtual void AddWriteTask(size_t offset, size_t length, const UID& uid,
            std::shared_ptr<char[]> data, 
            std::function<void(const std::shared_ptr<AMessage>&)> onDone) = 0;
    virtual void AddReadTask(size_t offset, size_t length, const UID& uid,
            std::function<void(const std::shared_ptr<AMessage>&)> onDone) = 0;
    virtual int GetMinionFD() = 0;
    virtual void OnMinionFDWakeup() = 0;
};  // class IMinionProxy

}   // namespace ilrd

#endif  // ILRD_RD1645_IMINION_PROXY_HPP
/**
* @file: Ticket.hpp
* @author: Ofir Nahshoni
* @brief: This is a header that defines the API for Ticket. This is an object
* that responsible to notify when a command was finished, and returned from
* the Minions.
*/

#ifndef ILRD_RD1645_TICKET_HPP
#define ILRD_RD1645_TICKET_HPP

#include <vector>                   // ilrd::vector<T>

#include "UID.hpp"
#include "TaskResult.hpp"           // ilrd::TaskResult
#include "IMinionProxy.hpp"         // ilrd::IMinionProxy
#include "DispatchCallback.hpp"     // ilrd::Dispatcher<Event>

namespace ilrd
{

class Ticket
{
public:
    Ticket(const std::vector<std::shared_ptr<IMinionProxy>>& proxies, 
                                                                const UID& uid);
    ~Ticket() = default;
    void RegisterToResultDispatcher(ACallback<std::shared_ptr<TaskResult>>* 
                                                                    callback);
    void OnMinionProxyDone(const std::shared_ptr<AMessage>& msgPtr);

private:
    UID m_uid;
    size_t m_counter;
    bool m_statusFirst;
    Dispatcher<std::shared_ptr<TaskResult>> m_dispatcherOnDone;
    std::vector<std::shared_ptr<IMinionProxy>> m_proxies;
};  // class Ticket

}   // namespace ilrd

#endif  // ILRD_RD1645_TICKET_HPP
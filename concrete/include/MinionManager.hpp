/**
* @file: MinionManager.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines an API for a manager object for
* the available Minions. It does the following: creation of a new Ticket, 
* registration of Tickets to a * Dispatcher, registration of Callbacks to 
* Reactor (another thread).
*/

#ifndef ILRD_RD1645_MINION_MANAGER_HPP
#define ILRD_RD1645_MINION_MANAGER_HPP

#include <thread>                   // std::jthread
#include <vector>                   // ilrd::vector<T>

#include "Ticket.hpp"               // ilrd::Ticket
#include "Reactor.hpp"              // ilrd::Reactor

namespace ilrd
{

class MinionManager
{
public:
    friend class Handleton;
    ~MinionManager() = default;
    void Init(size_t blockSize, 
            std::vector<std::shared_ptr<IMinionProxy>> minions);
    void RegisterNewTicket(ACallback<std::shared_ptr<Ticket>>* callback);
    void AddWriteTask(size_t offset, size_t length, const UID& uid, 
                    AMessage::MessageType msgType, 
                    std::shared_ptr<char[]> buffer);
    void AddReadTask(size_t offset, size_t length, const UID& uid, 
                    AMessage::MessageType msgType);
    
private:
    size_t m_blockSize;
    Reactor m_reactorToMinion;
    std::jthread m_reactorThread;
    std::vector<std::shared_ptr<IMinionProxy>> m_minions;
    Dispatcher<std::shared_ptr<Ticket>> m_dispatcherNewTicket;

    explicit MinionManager() = default;
    
    void ThreadFunc();
    std::pair<size_t, size_t> GetMinionsIndices(size_t offset);
    std::shared_ptr<Ticket> CreateTicket(size_t offset, const UID& uid);

    static std::shared_ptr<AMessage> CreateReadSend();
    static std::shared_ptr<AMessage> CreateReadResponse();
    static std::shared_ptr<AMessage> CreateWriteSend();
    static std::shared_ptr<AMessage> CreateWriteResponse();
};  // class MinionManager

}   // namespace ilrd

#endif  // ILRD_RD1645_MINION_MANAGER_HPP
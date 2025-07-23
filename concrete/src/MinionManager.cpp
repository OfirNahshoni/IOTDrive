/**
* @file: MinionManager.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of MinionManager.
*/

#include "AMessage.hpp"
#include "Handleton.hpp"
#include "MinionManager.hpp"

std::shared_ptr<ilrd::AMessage> ilrd::MinionManager::CreateReadSend()
{
    return std::make_shared<ReadSendMessage>();
}

std::shared_ptr<ilrd::AMessage> ilrd::MinionManager::CreateReadResponse()
{
    return std::make_shared<ReadResponseMessage>();
}

std::shared_ptr<ilrd::AMessage> ilrd::MinionManager::CreateWriteSend()
{
    return std::make_shared<WriteSendMessage>();
}

std::shared_ptr<ilrd::AMessage> ilrd::MinionManager::CreateWriteResponse()
{
    return std::make_shared<WriteResponseMessage>();
}

// init to: reactor, factory (create message)
void ilrd::MinionManager::Init(size_t blockSize, 
                            std::vector<std::shared_ptr<IMinionProxy>> minions)
{
    m_blockSize = blockSize;
    m_minions = minions;
    
    for (auto minion : m_minions)
    {
        m_reactorToMinion.Register(minion->GetMinionFD(), Mode::READ, 
                    [minion](int fd, Mode mode) {
                        (void)fd;
                        (void)mode;
                        minion->OnMinionFDWakeup();
                    });
    }                 

    m_reactorThread = std::jthread([this](){m_reactorToMinion.Run();});
}

void ilrd::MinionManager::RegisterNewTicket(ACallback<std::shared_ptr<Ticket>>* 
                                            callback)
{
    m_dispatcherNewTicket.Register(callback);
}

void ilrd::MinionManager::AddWriteTask(size_t offset, size_t length, 
                                    const UID& uid, 
                                    AMessage::MessageType msgType,
                                    std::shared_ptr<char[]> buffer)
{
    (void)msgType;

    auto [writeIdx, backupIdx] = GetMinionsIndices(offset);
    std::shared_ptr<Ticket> ticket = CreateTicket(offset, uid);
    m_dispatcherNewTicket.Notify(ticket);

    m_minions[writeIdx]->AddWriteTask(offset % m_blockSize, length, uid, buffer, 
                        [ticket](const std::shared_ptr<AMessage>& msgPtr) {
                            ticket->OnMinionProxyDone(msgPtr);
                        });
    
    m_minions[backupIdx]->AddWriteTask((offset % m_blockSize) + m_blockSize, 
                        length, uid, buffer, 
                        [ticket](const std::shared_ptr<AMessage>& msgPtr) {
                            ticket->OnMinionProxyDone(msgPtr);
                        });
}

void ilrd::MinionManager::AddReadTask(size_t offset, size_t length, 
                                    const UID& uid, 
                                    AMessage::MessageType msgType)
{
    (void)msgType;

    auto [readIdx, backupIdx] = GetMinionsIndices(offset);
    std::shared_ptr<Ticket> ticket = CreateTicket(offset, uid);
    m_dispatcherNewTicket.Notify(ticket);

    m_minions[readIdx]->AddReadTask(offset % m_blockSize, length, uid, 
                        [ticket](const std::shared_ptr<AMessage>& msgPtr) {
                            ticket->OnMinionProxyDone(msgPtr);
                        });

    m_minions[backupIdx]->AddReadTask((offset % m_blockSize) + m_blockSize, 
                                    length, uid,
                        [ticket](const std::shared_ptr<AMessage>& msgPtr) {
                            ticket->OnMinionProxyDone(msgPtr);
                        });
}

std::shared_ptr<ilrd::Ticket> ilrd::MinionManager::CreateTicket(size_t offset,
                                                                const UID& uid)
{
    auto [minionIdx, backupIdx] = GetMinionsIndices(offset);
    std::vector<std::shared_ptr<IMinionProxy>> copyVector = {
        m_minions[minionIdx], m_minions[backupIdx]
    };
    
    std::shared_ptr<Ticket> ticket = std::make_shared<Ticket>(copyVector, uid);
    
    return ticket;
}

std::pair<size_t, size_t> ilrd::MinionManager::GetMinionsIndices(size_t offset)
{
    return std::make_pair(offset / m_blockSize, 
                                (offset / m_blockSize + 1) % m_minions.size());
}
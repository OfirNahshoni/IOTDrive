/**
* @file: Ticket.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of Ticket. It's
* responsible for transfering the TaskResult (final result of Command/s) to
* the ResponseManager.
*/

#include <cstring>          // strcpy
#include <iostream>         // for debug

#include "Ticket.hpp"

ilrd::Ticket::Ticket(const std::vector<std::shared_ptr<IMinionProxy>>& proxies,
                    const UID& uid) :
                    m_uid(uid), m_counter(2),
                    m_proxies(proxies)
{ }

void ilrd::Ticket::RegisterToResultDispatcher(ACallback<std::shared_ptr<
                                                        TaskResult>>* callback)
{
    m_dispatcherOnDone.Register(callback);
}

void ilrd::Ticket::OnMinionProxyDone(const std::shared_ptr<AMessage>& msg)
{
    std::shared_ptr<TaskResult> taskResult;

    if (--m_counter == 0)
    {
        if (msg->GetClassType() == AMessage::ClassType::READ_RESPONSE)
        {
            auto readResponse = std::static_pointer_cast<ReadResponseMessage>(msg);
            std::shared_ptr<char[]> bufferPtr(new char[msg->GetLength()]);
                                
            std::memcpy(bufferPtr.get(), readResponse->GetBuffer(), 
                                                            msg->GetLength());

            taskResult = std::make_shared<TaskResult>(readResponse->GetStatus(),
                                                        TaskResult::RES_READ,
                                                        readResponse->GetUID(),
                                                        msg->GetLength(),
                                                        bufferPtr);
            m_dispatcherOnDone.Notify(taskResult);
        }
        else if (msg->GetClassType() == AMessage::ClassType::WRITE_RESPONSE)
        {
            auto writeResponse = std::static_pointer_cast<WriteResponseMessage>(msg);
            
            taskResult = std::make_shared<TaskResult>(
                                (writeResponse->GetStatus()),
                                TaskResult::RES_WRITE,
                                writeResponse->GetUID(),
                                msg->GetLength());
                                
            m_dispatcherOnDone.Notify(taskResult);
        }
    }
}
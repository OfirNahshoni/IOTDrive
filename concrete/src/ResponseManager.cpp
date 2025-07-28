/**
* @file: ResponseManager.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of ResponseManager.
* ResponseManager is responsible for mapping UID (of Tickets) to IResponse
* pointer, registration of Ticket to its dispatchers.
*/

#include <iostream>

#include "Factory.hpp"
#include "NBDProxy.hpp"
#include "ATaskArgs.hpp"
#include "ReadResponse.hpp"
#include "WriteResponse.hpp"
#include "MinionManager.hpp"
#include "ResponseManager.hpp"

ilrd::ResponseManager::ResponseManager() : 
                        m_newTicketCB(*this, &ResponseManager::OnNewTicket),
                        m_ticketDoneCB(*this, &ResponseManager::OnTicketDone),
                        m_newTaskArgsCB(*this, &ResponseManager::OnNewTaskArgs)
{ }

void ilrd::ResponseManager::OnNewTicket(std::shared_ptr<Ticket> ticket)
{
    ticket->RegisterToResultDispatcher(&m_ticketDoneCB);
}

void ilrd::ResponseManager::RemoveTicketFromMap(const UID& uid)
{
    std::unique_lock lock(m_mutex);

    if(m_map.contains(uid))
    {
        std::shared_ptr<IResponse> response = m_map.at(uid);
        m_map.erase(uid);
        lock.unlock();
    }
}

bool ilrd::ResponseManager::IsTicketInMap(const UID& uid)
{
    std::unique_lock lock(m_mutex);
    return m_map.contains(uid);
}

void ilrd::ResponseManager::OnNewTaskArgs(std::shared_ptr<ATaskArgs> taskArgs)
{
    std::unique_lock lock(m_mutex);
    m_map[taskArgs->GetUID()] = Handleton::GetInstance<Factory<int, 
                                    IResponse>>()->Create(taskArgs->GetKey());
}

void ilrd::ResponseManager::OnTicketDone(std::shared_ptr<TaskResult> taskResult)
{
    std::cout << "[ResponseManager] Ticket UID done: " << 
                taskResult->GetUid().GetID() << std::endl;

    std::unique_lock lock(m_mutex);
    auto response = m_map.at(taskResult->GetUid());
    m_map.erase(taskResult->GetUid());
    lock.unlock();

    if (taskResult->GetStatus())
    {
        response->OnSuccess(*taskResult);
    }
    else
    {
        response->OnFailure(*taskResult);
    }
}

void ilrd::ResponseManager::Init(NBDProxy& nbdProxy)
{
    Handleton::GetInstance<Factory<int, IResponse>>()->Register(AREAD, [] {
        return std::make_shared<ReadResponse>();
    });
    Handleton::GetInstance<Factory<int, IResponse>>()->Register(AWRITE, [] {
        return std::make_shared<WriteResponse>();
    });

    Handleton::GetInstance<MinionManager>()->RegisterNewTicket(&m_newTicketCB);
    
    nbdProxy.RegisterForNewTaskArgs(&m_newTaskArgsCB);
}
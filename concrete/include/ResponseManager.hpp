/**
* @file: ResponseManager.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the API for Responses coming from
* ready Tickets. It's responsible:
* 1) register OnNewTask to dispatcher of NBDProxy (and inside creates IResponse)
* 2) 
*/

#ifndef ILRD_RD1645_RESPONSE_MANAGER_HPP
#define ILRD_RD1645_RESPONSE_MANAGER_HPP

#include <map>                      // std::map

#include "Ticket.hpp"               // ilrd::Ticket
#include "NBDProxy.hpp"             // ilrd::NBDProxy
#include "IResponse.hpp"            // ilrd::IResponse
#include "Handleton.hpp"            // ilrd::Handleton

namespace ilrd
{

class ResponseManager
{
public:
    friend class Handleton;
    ~ResponseManager() = default;
    void Init(NBDProxy& nbdProxy);
    void OnNewTicket(std::shared_ptr<Ticket> ticket);
    void RemoveTicketFromMap(const UID& uid);
    bool IsTicketInMap(const UID& uid);
    void OnNewTaskArgs(std::shared_ptr<ATaskArgs> taskArgs);
    void OnTicketDone(std::shared_ptr<TaskResult> taskResult);

private:
    std::mutex m_mutex;
    std::map<UID, std::shared_ptr<IResponse>> m_map;
    Callback<std::shared_ptr<Ticket>, ResponseManager> m_newTicketCB;
    Callback<std::shared_ptr<TaskResult>, ResponseManager> m_ticketDoneCB;
    Callback<std::shared_ptr<ATaskArgs>, ResponseManager> m_newTaskArgsCB;

    explicit ResponseManager();
};  // class ResponseManager

}   // namespace ilrd

#endif  // ILRD_RD1645_RESPONSE_MANAGER_HPP
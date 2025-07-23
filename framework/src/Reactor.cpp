/**
* @file: Reactor.cpp
* @author: Ofir Nahshoni
* @brief: This is a file that implements the API of Reactor.hpp.
* @reviewer: Ofir1st
* @status: APPROVED
*/

#include "Reactor.hpp"

ilrd::Reactor::Reactor(std::unique_ptr<ilrd::IListener> listener): 
                                        m_isRunning(false), m_listener()
{ 
    m_listener.swap(listener);
}

void ilrd::Reactor::Register(int fd, ilrd::Mode mode, 
                            std::function<void(int, Mode)> func)
{
    m_listenersMap.emplace(std::make_pair(fd, mode), func);
}

void ilrd::Reactor::Unregister(int fd, Mode mode)
{
    m_listenersMap.erase(std::pair<int, Mode>(fd, mode));
}

void ilrd::Reactor::Run()
{
    m_isRunning = true;

    while (m_isRunning)
    {
        std::vector<std::pair<int, Mode>> allFDs;
        allFDs.reserve(m_listenersMap.size());

        for (const auto& item : m_listenersMap)
        {
            allFDs.emplace_back(item.first);
        }

        std::vector<std::pair<int, Mode>> activeFDs;

        try
        {
            activeFDs = m_listener->Listen(allFDs);
        }
        catch (...)
        {
            continue;
        }

        for (const auto& fdPair : activeFDs)
        {
            auto iter = m_listenersMap.find(fdPair);

            if (iter != m_listenersMap.end())
            {
                iter->second(fdPair.first, fdPair.second);
            }
        }
    }
}

void ilrd::Reactor::Stop()
{
    m_isRunning = false;
}
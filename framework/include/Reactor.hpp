/**
* @file: Reactor.hpp
* @author: Ofir Nahshoni
* @brief: This is an API header file of general-purpose Reactor class.
* @reviewer: Ofir1st
* @status: APPROVED
*/

#ifndef ILRD_RD1645_REACTOR_HPP
#define ILRD_RD1645_REACTOR_HPP

#include <map>                      // std::map
#include <functional>               // std::function
#include <memory>                   // std::unique_ptr

#include "IListener.hpp"            // IListener
#include "LinuxListener.hpp"        // LinuxListener

namespace ilrd
{

class Reactor
{
public:
    friend class Handleton;
    Reactor(std::unique_ptr<IListener> listener =
                                            std::make_unique<LinuxListener>());
    ~Reactor() = default;
    void Register(int fd, Mode mode, std::function<void(int, Mode)> func);
    void Unregister(int fd, Mode mode);
    void Run();
    void Stop();

private:
    bool m_isRunning;
    std::unique_ptr<IListener> m_listener;
    std::map<std::pair<int, Mode>, std::function<void(int, Mode)>> m_listenersMap;
};  // class Reactor

}   // namespace ilrd

#endif  // ILRD_RD1645_REACTOR_HPP
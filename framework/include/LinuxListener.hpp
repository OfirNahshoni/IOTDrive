/**
* @file: Listener.hpp
* @author: Ofir Nahshoni
* @brief: This is a file that defines an interface class IListener to make
* the most portable listen function (like select() in linux).
* @reviewer: Ofir1st
* @status: APPROVED
*/

#ifndef ILRD_RD1645_LINUX_LISTENER_HPP
#define ILRD_RD1645_LINUX_LISTENER_HPP

#include "IListener.hpp"

namespace ilrd
{

class LinuxListener : public IListener
{
public:
    std::vector<std::pair<int, Mode>> Listen(std::vector<std::pair<int, Mode>>
                                                                        fds);
};  // class SelectListener
            
}   // namespace ilrd

#endif  // ILRD_RD1645_LINUX_LISTENER_HPP
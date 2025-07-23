/**
* @file: Listener.cpp
* @author: Ofir Nahshoni
* @brief: This is a file that implements the API of Reactor.hpp.
* @reviewer: Ofir1st
* @status: APPROVED
*/

#include <sys/select.h>     // select
#include <iostream>

#include "LinuxListener.hpp"    // ilrd::LinuxListener

using namespace ilrd;

std::vector<std::pair<int, Mode>> LinuxListener::Listen(
                                        std::vector<std::pair<int, Mode>> fds)
{
    fd_set readFDs;
    fd_set writeFDs;

    FD_ZERO(&readFDs);
    FD_ZERO(&writeFDs);

    int maxFD = -1;

    for (const auto& [fd, mode] : fds)
    {
        if (mode == Mode::READ)
        {
            FD_SET(fd, &readFDs);
        }
        else
        {
            FD_SET(fd, &writeFDs);
        }

        maxFD = std::max(fd, maxFD);
    }

    int activity = select(maxFD + 1, &readFDs, &writeFDs, nullptr, nullptr);

    if (activity == -1)
    {
        throw std::runtime_error("failed in select()");
    }

    std::vector<std::pair<int, Mode>> activeFDs;
    activeFDs.reserve(activity);

    for (const auto& [fd, mode] : fds)
    {
        if ((mode == Mode::READ && FD_ISSET(fd, &readFDs)) ||
            (mode == Mode::WRITE && FD_ISSET(fd, &writeFDs)))
        {
            activeFDs.emplace_back(fd, mode);
        }
    }

    return activeFDs;
}
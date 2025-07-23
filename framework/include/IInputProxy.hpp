

#ifndef ILRD_RD1645_IINPUT_PROXY_HPP
#define ILRD_RD1645_IINPUT_PROXY_HPP

#include "ITaskArgs.hpp"    // ITaskArgs
#include "IListener.hpp"    // listeners::Mode

namespace ilrd
{

class IInputProxy
{
public:
    virtual int GetSocketFD() const = 0;
    virtual std::shared_ptr<ITaskArgs> GetTaskArgs(int fd, Mode mode) = 0;
};

}   // namespace ilrd

#endif  // ILRD_RD1645_IINPUT_PROXY_HPP


#ifndef ILRD_RD1645_ITASK_ARGS_HPP
#define ILRD_RD1645_ITASK_ARGS_HPP

namespace ilrd
{
    
class ITaskArgs
{
public:
    virtual int GetKey() const = 0;   // returns fd as int
};  // class ITaskArgs
    
}   // namespace ilrd

#endif  // ILRD_RD1645_ITASK_ARGS_HPP
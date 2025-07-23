

#ifndef ILRD_RD1645_FW_TPTASK_HPP
#define ILRD_RD1645_FW_TPTASK_HPP

#include "ITPTask.hpp"          // ilrd::ITPTask
#include "ITaskArgs.hpp"        // ilrd::ITaskArgs

namespace ilrd
{

class FWTPTask : public ilrd::threadpool::ITPTask
{
public:
    FWTPTask(std::shared_ptr<ITaskArgs> ptrTaskArgs);
    ~FWTPTask() = default;
    void Run();

private:
    std::shared_ptr<ITaskArgs> m_ptrTaskArgs;
};  // class FWTPTask

}   // namespace ilrd

#endif  // ILRD_RD1645_FW_TPTASK_HPP
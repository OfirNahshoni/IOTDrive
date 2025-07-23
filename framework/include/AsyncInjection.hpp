/**
* @file: AsyncInjection.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the API of Asynchronous Injection,
* which is a special feature that a task manages itself. If a response doesn't
* arrive, then it inserts itself to the Scheduler, and if it got a response, 
* then it deletes itself.
* @reviewer: Amit
* @status: APPROVED
*/

#ifndef ILRD_RD1645_ASYNC_INJECTION_HPP
#define ILRD_RD1645_ASYNC_INJECTION_HPP

#include <functional>           // std::function

#include "Scheduler.hpp"        // ilrd::Scheduler
#include "ISchedulerTask.hpp"   // ilrd::ISchedulerTask

namespace ilrd
{

class AsyncInjection
{
public:
    /*
        func returns true: deletes itself.
        func returns false: adds itself to scheduler.
    */
    AsyncInjection(std::function<bool()> func, std::chrono::milliseconds interval);
    void PerformAction();

private:
    ~AsyncInjection() = default;
    void AddTaskToSched();

    class AsyncInjTask: public ilrd::ISchedulerTask
    {
    public:
        AsyncInjTask(AsyncInjection& ai);
        void Execute();

    private:
        AsyncInjection& m_ai;
    };  // class AsyncInjTask

    std::function<bool()> m_func;
    std::chrono::milliseconds m_interval;
    std::shared_ptr<AsyncInjTask> m_taskToAdd;
};  // class AsyncInjection

}   // namespace ilrd

#endif  // ILRD_RD1645_ASYNC_INJECTION_HPP
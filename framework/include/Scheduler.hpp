/**
* @file: Scheduler.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the API for a scheduler that
* schedules tasks from type ISchedulerTask.
* @reviewer: Zack
* @status: APPROVED
*/

#ifndef ILRD_RD1645_SHCEDULER_HPP
#define ILRD_RD1645_SHCEDULER_HPP

#include <chrono>                   // std::chrono
#include <mutex>                    // std::mutex
#include <memory>                   // std::shared_ptr
#include <atomic>                   // std::atomic_uint
#include <csignal>                  // sigval, sigevent
#include <queue>                    // std::priority_queue
#include <condition_variable>       // std::condition_variable

#include "ISchedulerTask.hpp"       // ilrd::ISchedulerTask

namespace ilrd
{

class Scheduler
{
public:
    void AddTask(std::shared_ptr<ISchedulerTask> task, 
                std::chrono::milliseconds ms);
    Scheduler(const Scheduler& other) = delete;
    Scheduler& operator=(const Scheduler& rhs) = delete;
    ~Scheduler();
    
private:
    Scheduler();
    friend class Handleton;
    void ThreadWork();
    static void ThreadFunc(sigval sval);

    class SchedTask : public ISchedulerTask
    {
    public:
        SchedTask(std::shared_ptr<ISchedulerTask> task, 
                std::chrono::milliseconds ms);
        void Execute();
        std::chrono::time_point<std::chrono::system_clock> GetExecTime() const;
        bool operator<(const SchedTask& rhs) const;

    private:
        std::shared_ptr<ISchedulerTask> m_task;
        std::chrono::time_point<std::chrono::system_clock> m_execTime;
    };  // class SchedTask

    class Timer
    {
    public:
        explicit Timer(void(*timerDoneFunc)(sigval sval), void* scheduler);
        ~Timer();
        void Start(std::chrono::time_point<std::chrono::system_clock> execTime);

    private:
        timer_t m_timer;
        itimerspec m_tspec;
        sigevent m_sigevent;
    };  // class Timer

    Timer m_timer;
    std::mutex m_lock;
    std::atomic_uint m_counter;
    std::condition_variable m_cond;
    std::priority_queue<SchedTask> m_queue;
};  // class Scheduler

}   // namespace ilrd

#endif  // ILRD_RD1645_SHCEDULER_HPP
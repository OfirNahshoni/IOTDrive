/**
* @file: Scheduler.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the Scheduler.hpp API. 
* @reviewer: Zack
* @status: APPROVED
*/

#include <iostream>             // std::cerr

#include "Scheduler.hpp"        // ilrd::Scheduler

ilrd::Scheduler::Scheduler() : m_timer(ThreadFunc, this)
{ }

ilrd::Scheduler::~Scheduler()
{
    try
    {
        std::unique_lock lock(m_lock);
        m_cond.wait(lock, [this] { return m_counter.load() == 0; });
    }
    catch(...)
    {
        std::cerr << "failed to lock mutex" << std::endl;
    }
}

void ilrd::Scheduler::AddTask(std::shared_ptr<ISchedulerTask> task,
                            std::chrono::milliseconds ms)
{
    SchedTask schedTask(task, ms);
    
    std::unique_lock lock(m_lock);
    ++m_counter;

    if (!m_queue.empty() && (m_queue.top() < schedTask))
    {
        m_timer.Start(schedTask.GetExecTime());
    }

    m_queue.push(schedTask);
}

void ilrd::Scheduler::ThreadWork()
{
    std::unique_lock lock(m_lock);
    SchedTask task = m_queue.top();
    m_queue.pop();
    lock.unlock();
    
    task.Execute();

    lock.lock();
    --m_counter;

    if (!m_queue.empty())
    {
        m_timer.Start(m_queue.top().GetExecTime());
    }
    else if (m_counter.load() == 0)
    {
        m_cond.notify_one();
    }
}

void ilrd::Scheduler::ThreadFunc(sigval sval)
{
    Scheduler* sched = static_cast<Scheduler*>(sval.sival_ptr);

    sched->ThreadWork();
}

/*----------------------------class SchedTask---------------------------------*/
ilrd::Scheduler::SchedTask::SchedTask(std::shared_ptr<ISchedulerTask> task,
                            std::chrono::milliseconds ms) : 
                            m_task(task), 
                            m_execTime(std::chrono::system_clock::now() + ms)
{ }

void ilrd::Scheduler::SchedTask::Execute()
{
    m_task->Execute();
}

std::chrono::time_point<std::chrono::system_clock> ilrd::Scheduler::SchedTask::
                        GetExecTime() const
{
    return m_execTime;
}

bool ilrd::Scheduler::SchedTask::operator<(const SchedTask& rhs) const
{
    return (m_execTime > rhs.GetExecTime());
}

/*------------------------------class Timer-----------------------------------*/
ilrd::Scheduler::Timer::Timer(void(*timerDoneFunc)(sigval sval), 
            void* scheduler) : m_timer(), m_tspec({0, 0}, {0, 0}), m_sigevent()
{

    m_sigevent.sigev_notify = SIGEV_THREAD;
    m_sigevent.sigev_notify_function = timerDoneFunc;
    m_sigevent.sigev_value.sival_ptr = scheduler;

    if (timer_create(CLOCK_REALTIME, &m_sigevent, &m_timer) == -1)
    {
        throw std::runtime_error("failed to create timer");
    }
}

ilrd::Scheduler::Timer::~Timer()
{
    timer_delete(m_timer);
}

void ilrd::Scheduler::Timer::Start(std::chrono::time_point
                                    <std::chrono::system_clock> execTime)
{
    m_tspec.it_value.tv_sec = std::chrono::system_clock::to_time_t(execTime);
    m_tspec.it_value.tv_nsec = (execTime - std::chrono::system_clock::
                            from_time_t(m_tspec.it_value.tv_sec)).count() + 1;

    if (timer_settime(m_timer, TIMER_ABSTIME, &m_tspec, nullptr) == -1)
    {
        throw std::runtime_error("failed to start timer");
    }
}
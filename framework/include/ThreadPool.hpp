/**
* @file: ThreadPool.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file for Thread Pool mechanism.
* @reviewer: Ofir1st
* @status: APPROVED
*/

#ifndef ILRD_RD1645_THREAD_POOL_HPP
#define ILRD_RD1645_THREAD_POOL_HPP

#include <map>                      // std::map
#include <thread>                   // std::jthread
#include <memory>                   // std::shared_ptr

#include "TSWaitableQueue.hpp"      // WaitableQueue<T, DS>
#include "ITPTask.hpp"              // ITPTask, FunctionTask, FutureTask

namespace ilrd
{

namespace threadpool
{

class ThreadPool
{
public:
    enum Priority
    {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3
    };

    explicit ThreadPool(size_t n = std::thread::hardware_concurrency() - 1);
    ~ThreadPool();
    void AddTask(std::shared_ptr<ITPTask> task, Priority priority = LOW);
    void Pause();
    void Resume();
    void SetNumOfThreads(size_t n);

private:
    class TPTask;
    size_t m_maxtid;
    size_t m_numOfThreads;
    std::mutex m_mutexSyncStop;
    std::atomic_bool m_isPaused;
    TSWaitableQueue<size_t> m_deletionsQueue;
    std::condition_variable m_condThreadWait;
    std::counting_semaphore<> m_threadWaitSem;
    static thread_local bool m_isThreadStopped;
    std::map<size_t, std::jthread> m_threadsMap;
    TSWaitableQueue<TPTask, std::priority_queue<TPTask>> m_tasksQueue;

    enum InnerPriority
    {
        DTOR = 0,
        ILOW = 1,
        IMEDIUM = 2,
        IHIGH = 3,
        CRITICAL = 19
    };

    class TPTask
    {
    public:
        TPTask(std::shared_ptr<ITPTask> task, 
                InnerPriority priority);
        void Run();
        bool operator<(const TPTask& rhs) const;
        
    private:
        InnerPriority m_priority;
        std::shared_ptr<ITPTask> m_itptask;
        std::chrono::time_point<std::chrono::steady_clock> m_addTime;
    };
    
    void AddThreads(size_t nThreads);
    void RemoveThreads(size_t nThreads);
    
    static void KillTh();
    static void PauseTh(ThreadPool& tpool);
    static void ThreadPop(ThreadPool& tpool, size_t tid);
};  // class ThreadPool

}   // namespace threadpool

}   // namespace ilrd

#endif  // ILRD_RD1645_THREAD_POOL_HPP

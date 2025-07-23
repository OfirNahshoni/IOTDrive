/**
* @file: ThreadPool.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API functions ThreadPool.
* @reviewer: Ofir1st
* @status: APPROVED
*/

#include "ThreadPool.hpp"   // ThreadPool

thread_local bool ilrd::threadpool::ThreadPool::m_isThreadStopped = true;


/*----------------------------Thread function---------------------------------*/
void ilrd::threadpool::ThreadPool::ThreadPop(ThreadPool& tpool, size_t idx)
{
    while (m_isThreadStopped)
    {
        TPTask taskToExecute(nullptr, ILOW);
        tpool.m_tasksQueue.Pop(taskToExecute);
        taskToExecute.Run();
    }

    tpool.m_deletionsQueue.Push(idx);
}

/*----------------------------Tasks functions---------------------------------*/
void ilrd::threadpool::ThreadPool::PauseTh(ThreadPool& tpool)
{
    std::unique_lock lock(tpool.m_mutexSyncStop);
    tpool.m_threadWaitSem.release();
    tpool.m_condThreadWait.wait(lock, [&tpool] { return !tpool.m_isPaused; });
}

void ilrd::threadpool::ThreadPool::KillTh()
{
    m_isThreadStopped = false;
}

/*----------------------------Helper functions--------------------------------*/
void ilrd::threadpool::ThreadPool::AddThreads(size_t nThreads)
{
    for (size_t i = 0; i < nThreads; ++i, ++m_maxtid)
    {
        m_threadsMap.emplace(m_maxtid, std::jthread(ThreadPop, std::ref(*this), 
                            m_maxtid));
    }
}

void ilrd::threadpool::ThreadPool::RemoveThreads(size_t nThreads)
{
    size_t idx = 0;
    std::shared_ptr<ITPTask> itpTask(new FunctionTask<>(KillTh));
    
    for (size_t i = 0; i < nThreads; ++i)
    {
        AddTask(itpTask, static_cast<Priority>(CRITICAL));
        std::unique_lock lock(m_mutexSyncStop);
        m_condThreadWait.notify_one();
    }
    
    for (size_t i = 0; i < nThreads; ++i)
    {
        m_deletionsQueue.Pop(idx);
        m_threadsMap.at(idx).join();
        m_threadsMap.erase(idx);
    }
}

/*-------------------------------ThreadPool-----------------------------------*/
ilrd::threadpool::ThreadPool::ThreadPool(size_t numOfThreads): 
                            m_maxtid(0), 
                            m_numOfThreads(numOfThreads), 
                            m_threadWaitSem(0)
{
    for (; m_maxtid < numOfThreads; ++m_maxtid)
    {
        m_threadsMap.emplace(m_maxtid, std::jthread(ThreadPop, std::ref(*this), 
                            m_maxtid));
    }
}

ilrd::threadpool::ThreadPool::~ThreadPool()
{
    Resume();

    for (size_t i = 0; i < m_numOfThreads; ++i)
    {
        std::shared_ptr<threadpool::ITPTask> task(new FunctionTask<>(KillTh));
        m_tasksQueue.Push(TPTask(task, DTOR));
    }

    for (auto iter = m_threadsMap.begin(); iter != m_threadsMap.end(); ++iter)
    {
        iter->second.join();
    }
}

void ilrd::threadpool::ThreadPool::AddTask(std::shared_ptr<ITPTask> task, 
                                            Priority priority)
{
    m_tasksQueue.Push(TPTask(task, static_cast<InnerPriority>(priority)));
}

void ilrd::threadpool::ThreadPool::Pause()
{
    m_isPaused = true;
    std::shared_ptr<threadpool::ITPTask> itpTask(
                                new FunctionTask<ThreadPool&>(PauseTh, *this));

    for (size_t i = 0; i < m_numOfThreads; ++i)
    {
        m_tasksQueue.Push(TPTask(itpTask, CRITICAL));
    }

    for (size_t i = 0; i < m_numOfThreads; ++i)
    {
        m_threadWaitSem.acquire();
    }
}

void ilrd::threadpool::ThreadPool::Resume()
{
    m_isPaused = false;
    std::unique_lock<std::mutex> lock(m_mutexSyncStop);
    m_condThreadWait.notify_all();
}

void ilrd::threadpool::ThreadPool::SetNumOfThreads(size_t numOfThreads)
{
    if (numOfThreads > m_numOfThreads)
    {
        AddThreads(numOfThreads - m_numOfThreads);
    }
    else
    {
        RemoveThreads(m_numOfThreads - numOfThreads);
    }

    m_numOfThreads = numOfThreads;
}

/*----------------------------------TPTask------------------------------------*/
ilrd::threadpool::ThreadPool::TPTask::TPTask(
            std::shared_ptr<threadpool::ITPTask> task, InnerPriority priority) : 
                                    m_priority(priority),
                                    m_itptask(task),
                                    m_addTime(std::chrono::steady_clock::now())
{ }

void ilrd::threadpool::ThreadPool::TPTask::Run()
{
    m_itptask->Run();
}

bool ilrd::threadpool::ThreadPool::TPTask::operator<(const TPTask& rhs) const
{
    return ((m_priority == rhs.m_priority) ? 
            (m_addTime > rhs.m_addTime) : 
            (m_priority < rhs.m_priority));
}

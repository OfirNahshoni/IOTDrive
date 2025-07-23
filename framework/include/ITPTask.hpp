/**
* @file: ITPTask.hpp
* @author: Ofir Nahshoni
* @brief: This header file includes different Tasks class void (FunctionTask)
* and with return value (FutureTask).
* @reviewer: Ofir1st
* @status: APPROVED
*/

#ifndef ILRD_RD1645_ITP_TASK_HPP
#define ILRD_RD1645_ITP_TASK_HPP

#include <tuple>            // std::tuple
#include <functional>       // std::function
#include <semaphore>        // std::semaphore

namespace ilrd
{

namespace threadpool
{

class ITPTask
{
public:
    virtual void Run() = 0;
    virtual ~ITPTask() = default;
};  // class ITPTask

template <typename ...ARGS>
class FunctionTask : public ITPTask
{
public:
    FunctionTask(std::function<void(ARGS...)> funct, ARGS... args);
    ~FunctionTask() = default;
    void Run();

private:
    std::tuple<ARGS...> m_args;
    std::function<void(ARGS...)> m_funct;
};  // class FunctionTask

template <typename RETURN, typename ...ARGS>
class FutureTask : public ITPTask
{
public:
    FutureTask(std::function<RETURN(ARGS...)> funct, ARGS... args);
    ~FutureTask() = default;
    void Run();
    RETURN& Get();

private:
    RETURN m_retVal;
    std::binary_semaphore m_sem;
    std::tuple<RETURN(ARGS...)> m_args;
    std::function<RETURN(ARGS...)> m_funct;
};  // class FutureTask

template <typename ...ARGS>
FunctionTask<ARGS...>::FunctionTask(std::function<void(ARGS...)> funct, 
                                    ARGS... args) : 
                                    m_args(args...),
                                    m_funct(funct)
{ }

template <typename ...ARGS>
void FunctionTask<ARGS...>::Run()
{
    std::apply(m_funct, m_args);
}

template <typename RETURN, typename ...ARGS>
FutureTask<RETURN, ARGS...>::FutureTask(std::function<RETURN(ARGS...)> funct, 
                                        ARGS... args) : 
                                        m_funct(funct), 
                                        m_args(args...),
                                        m_sem(0)
{ }

template <typename RETURN, typename ...ARGS>
void FutureTask<RETURN, ARGS...>::Run()
{
    m_retVal = std::apply(m_funct, m_args);
    m_sem.release();
}

template <typename RETURN, typename ...ARGS>
RETURN& FutureTask<RETURN, ARGS...>::Get()
{
    m_sem.acquire();
    return m_retVal;
}

}   // namespace threadpool

}   // namespace ilrd

#endif  // ILRD_RD1645_ITP_TASK_HPP
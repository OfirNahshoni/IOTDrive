/**
* @file: AsyncInjection.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the AsyncInjection API.
* @reviewer: Amit
* @status: APPROVED
*/

#include "Handleton.hpp"
#include "AsyncInjection.hpp"

ilrd::AsyncInjection::AsyncInjection(std::function<bool()> func, 
                            std::chrono::milliseconds interval) : 
                            m_func(func),
                            m_interval(interval),
                            m_taskToAdd(std::make_shared<AsyncInjTask>(*this))
{
    AddTaskToSched();
}

void ilrd::AsyncInjection::PerformAction()
{
    if (m_func())
    {
        delete this;
    }
    else
    {
        AddTaskToSched();
    }
}

void ilrd::AsyncInjection::AddTaskToSched()
{
    ilrd::Handleton::GetInstance<ilrd::Scheduler>()->AddTask(m_taskToAdd, 
                                                            m_interval);
}

ilrd::AsyncInjection::AsyncInjTask::AsyncInjTask(AsyncInjection& ai): m_ai(ai)
{ }

void ilrd::AsyncInjection::AsyncInjTask::Execute()
{
    m_ai.PerformAction();
}
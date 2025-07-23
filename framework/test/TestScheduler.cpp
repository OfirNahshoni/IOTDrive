#include <iostream>

#include "Scheduler.hpp"

namespace tasks
{

class PrintTask : public ilrd::ISchedulerTask
{
public:
    PrintTask(int i);
    void Execute();

private:
    int m_i;
};

PrintTask::PrintTask(int i) : m_i(i)
{ }

void PrintTask::Execute()
{
    std::cout << "i = " << m_i << std::endl;
}

class SpecialTask : public ilrd::ISchedulerTask
{
public:
    void Execute();
};  // class SpecialTask

void SpecialTask::Execute()
{
    ilrd::Scheduler* sched = ilrd::Handleton::GetInstance<ilrd::Scheduler>();
    std::cout << "SpecialTask executing:" << std::endl;
    sched->AddTask(std::make_shared<PrintTask>(123456789), 
                    std::chrono::milliseconds(5000));
    sched->AddTask(std::make_shared<PrintTask>(111111111),
                    std::chrono::milliseconds(1000));
}

}   // namespace tasks


void BasicTestsForScheduler();
void SpecialTestsForScheduler();

int main()
{
    BasicTestsForScheduler();
    SpecialTestsForScheduler();

    return 0;
}

void BasicTestsForScheduler()
{
    size_t n = 5;
    size_t ms = 5000;
    ilrd::Scheduler* sched = ilrd::Handleton::GetInstance<ilrd::Scheduler>();

    std::cout << "Basic Tests:" << std::endl;
    
    for (size_t i = 1; i <= n; ++i, ms -= 1000)
    {
        sched->AddTask(std::make_shared<tasks::PrintTask>(i),
                            std::chrono::milliseconds(ms));
    }
}

void SpecialTestsForScheduler()
{
    ilrd::Scheduler* sched = ilrd::Handleton::GetInstance<ilrd::Scheduler>();

    sched->AddTask(std::make_shared<tasks::SpecialTask>(),
                            std::chrono::milliseconds(11000));
}
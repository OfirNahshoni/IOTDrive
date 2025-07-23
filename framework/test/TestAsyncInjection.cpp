/**
* @file: TestAsyncInjection.cpp
* @author: Ofir Nahshoni
* @brief: This is a test file for Asynchronous Injection - Asynchronous
* behavior in Synchronous system.
*/

#include <iostream>

#include "AsyncInjection.hpp"   // ilrd::AsyncInjection

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

}   // namespace tasks

size_t g_counter = 0;

bool Response();
bool NoResponse();

void TestsFoAsyncInjection();

int main()
{
    TestsFoAsyncInjection();

    return 0;
}

bool Response()
{
    std::cout << "Task that returns true" << std::endl;
    return true;
}

bool NoResponse()
{
    ++g_counter;
    std::cout << "failed attempt " << g_counter << std::endl;
    return (g_counter >= 5);
}

void TestsFoAsyncInjection()
{
    new ilrd::AsyncInjection(Response,
                                    std::chrono::milliseconds(5000));
    new ilrd::AsyncInjection(NoResponse,
                                    std::chrono::milliseconds(500));
}
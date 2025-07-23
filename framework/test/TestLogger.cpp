/**
* @file: TestLogger.cpp
* @author: Ofir Nahshoni
* @brief: Test file forL Logger (thread-safe).
*/

#include <thread>           // std::jthread

#include "Logger.hpp"       // Logger
#include "Handleton.hpp"    // Handleton

void LogErrorThread(size_t i);
void TestsForLogger();

int main()
{
    TestsForLogger();

    return 0;
}

void LogDebugThread(size_t i)
{
    std::string msg("thread " + std::to_string(i));
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log(msg);
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log(msg,
                                                ilrd::Logger::WARNING);
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log(msg,
                                                    ilrd::Logger::ERROR);
}

void TestsForLogger()
{
    const size_t numOfThreads = 5;
    std::jthread threads[numOfThreads];
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log("first write");
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log("second write");

    for (size_t i = 0; i < numOfThreads; ++i)
    {
        threads[i] = std::jthread(LogDebugThread, i);
    }
}

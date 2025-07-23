/**
* @file: TestThreadPool.cpp
* @author: Ofir Nahshoni
* @brief: This is the test file that test ThreadPool class.
*/

#include <iostream>

#include "ThreadPool.hpp"       // ThreadPool
#include "test_macros.h"        // GREEN, MAGENTA

// My Tests
void SleepTask();
void LowTask();
void MediumTask();
void HighTask();
void BasicTestsThreadPool();

// Ofir1st Tests
void Task1(int i);
void Task2(int i, char c);
int FutureTaskFunc(bool b);
void TestThreadPoolOfir1st();

int main()
{
    BasicTestsThreadPool();
    // TestThreadPoolOfir1st();
    PASS;

    return 0;
}

void SleepTask()
{
    sleep(5);
    std::cout << MAGENTA"finished sleeping" << std::endl;
}

void LowTask()
{
    sleep(1);
    std::cout << GREEN"task priority LOW" << std::endl;
}

void MediumTask()
{
    sleep(1);
    std::cout << GREEN"task priority MEDUIM" << std::endl;
}

void HighTask()
{
    std::cout << GREEN"task priority HIGH" << std::endl;
}

void BasicTestsThreadPool()
{
    size_t numOfThreads = 4;
    ilrd::threadpool::ThreadPool tp(numOfThreads);
    std::shared_ptr<ilrd::threadpool::ITPTask> sleepTask(
                            new ilrd::threadpool::FunctionTask<>(SleepTask));
    std::shared_ptr<ilrd::threadpool::ITPTask> lowTask(
                            new ilrd::threadpool::FunctionTask<>(LowTask));
    std::shared_ptr<ilrd::threadpool::ITPTask> mediumTask(
                        new ilrd::threadpool::FunctionTask<>(MediumTask));
    std::shared_ptr<ilrd::threadpool::ITPTask> highTask(
                            new ilrd::threadpool::FunctionTask<>(HighTask));

    for (size_t i = 0; i < 4; ++i)
    {
        tp.AddTask(sleepTask, ilrd::threadpool::ThreadPool::MEDIUM);
    }
    
    sleep(2);

    std::cout << "Basic Tests:" << std::endl;

    for (size_t i = 0; i < 3; ++i)
    {
        tp.AddTask(mediumTask, ilrd::threadpool::ThreadPool::MEDIUM);
        tp.AddTask(lowTask, ilrd::threadpool::ThreadPool::LOW);
        tp.AddTask(highTask, ilrd::threadpool::ThreadPool::HIGH);
    }
}

void Task1(int i)
{
    std::cout << i << std::endl;
}

void Task2(int i, char c)
{
    std::cout << i << std::endl;
    std::cout << c << std::endl;
}

int FutureTaskFunc(bool b)
{
    sleep(1);
    return b ? 3 : 8;
}

// void TestThreadPoolOfir1st()
// {
//     ilrd::threadpool::ThreadPool tp(4);
//
//     std::function func1([] { Task1(1); });
//
//     std::shared_ptr<ilrd::threadpool::ITPTask> ifunc1(
//                                 new ilrd::threadpool::FunctionTask(func1));
//     // tp.AddTask(ifunc1, ilrd::HIGH);
//
//     std::function<void()> func2 = std::bind(Task1, 9);
//     std::shared_ptr<ilrd::threadpool::ITPTask> ifunc2(
//                                 new ilrd::threadpool::FunctionTask(func2));
//
//     std::function<int()> func3 = std::bind(FutureTaskFunc, false);
//     std::shared_ptr<ilrd::threadpool::ITPTask> ifunc3(
//                                     new ilrd::threadpool::FutureTask(func3));
//
//     std::function<void()> func4 = std::bind(Task2, 4, 'c');
//     std::shared_ptr<ilrd::threadpool::ITPTask> ifunc4(
//                                 new ilrd::threadpool::FunctionTask(func4));
//
//     std::cout << "Ofir1st Tests:" << std::endl;
//
//     tp.AddTask(ifunc4, ilrd::threadpool::ThreadPool::HIGH);
//
//     for(size_t i = 0; i < 10; ++i)
//     {
//         tp.AddTask(ifunc3, ilrd::threadpool::ThreadPool::HIGH);
//         tp.AddTask(ifunc2,
//                         ilrd::threadpool::ThreadPool::LOW); // prints 9
//         tp.AddTask(ifunc1,
//                         ilrd::threadpool::ThreadPool::MEDIUM); // prints 1
//         std::cout << static_cast<ilrd::threadpool::FutureTask<int>*>(
//                                 ifunc3.get())->Get() << std::endl; //prints 8
//     }
//     tp.SetNumOfThreads(8);
//
//     for(size_t i = 0; i < 10; ++i)
//     {
//         tp.AddTask(ifunc2, ilrd::threadpool::ThreadPool::MEDIUM);
//         tp.AddTask(ifunc1, ilrd::threadpool::ThreadPool::LOW);
//         if (i == 5)
//         {
//             tp.Pause();
//         }
//
//         if (i == 8)
//         {
//             tp.Resume();
//             std::cout << "resuming" << std::endl;
//             tp.SetNumOfThreads(3);
//         }
//     }
//
//     tp.Pause();
//     tp.SetNumOfThreads(5);
// }


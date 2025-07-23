/**
* @file: TestSingleton.cpp
* @author: Ofir Nahshoni
* @brief: A test file that tests the requirements of the ws "C++ Singleton",
* Phase A, Phase B.
*/

#include <vector>               // std::vector
#include <string>               // std::string
#include <thread>               // std::jthread

#include "test_macros.h"        // PASS
#include "BitSet.hpp"           // BitSet<N>
#include "Singleton.hpp"        // Singleton<T>

void ThreadFunc(int id);

void TestsSingletonPhaseA();
void TestsSingletonPhaseB();
void TestForSingletonDestruction();

int main()
{
    TestsSingletonPhaseA();
    std::cout << "--------------------" << std::endl << "Phase B:" << std::endl;
    TestsSingletonPhaseB();
    std::cout << "--------------------" << std::endl << "Destruction:" << std::endl;
    TestForSingletonDestruction();
    PASS;

    return 0;
}

void ThreadFunc(int id)
{
    std::string* instance = ilrd::Singleton<std::string>::GetInstance();
    instance->assign("Thread: " + std::to_string(id));
}

void TestsSingletonPhaseA()
{
    ilrd::BitSet<4>* instance = ilrd::Singleton<ilrd::BitSet<4>>::GetInstance();

    instance->Set(3, true);
    std::string str = instance->ToString();

    TEST("set one bit check", (str == "0100"), true);

    std::string* strInstance = ilrd::Singleton<std::string>::GetInstance();
    strInstance->assign("hello world");
    TEST("string assign check", (*strInstance == "hello world"), true);
}

void TestsSingletonPhaseB()
{
    const size_t numOfThreads = std::thread::hardware_concurrency() - 1;
    std::vector<std::jthread> threads;

    for (size_t i = 0; i < numOfThreads; ++i)
    {
        threads.emplace_back(ThreadFunc, i);
    }

    std::cout << "Final Singleton-String value: " << std::endl
                << ilrd::Singleton<std::string>::GetInstance()->c_str()
                << std::endl;
}

void TestForSingletonDestruction()
{
    std::string* instance = ilrd::Singleton<std::string>::GetInstance();
    instance->assign("before exit");
    std::cout << "before exit: " << instance->c_str() << std::endl;

    atexit([]() {
        std::cout << "Singleton destruction test: "
                    << ilrd::Singleton<std::string>::GetInstance()->c_str()
                    << std::endl;
    });
}
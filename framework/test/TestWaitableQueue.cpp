/**
* @file: TestWaitableQueue.cpp
* @author: Ofir Nahshoni
* @brief: This is a test file for testing the generic (templated) thread-safe
* Waitable Queue API. The API header includes Waitable queues classes.
*/

#include <cstddef>                  // size_t
#include <string>                   // std::string
#include <iostream>                 // std::ostream
#include <vector>                   // std::vector<T>
#include <thread>                   // thread, this_thread

#include "test_macros.h"            // PASS, TEST
#include "TSWaitableQueue.hpp"      // TSWaitableQueue<T, DS>

using namespace ilrd;

void ProducerThread(TSWaitableQueue<int>& queue, size_t iterations, int seconds);
void ConsumerBlockingThread(TSWaitableQueue<int>& queue, size_t iterations);

// std::queue tests
void BasicTestsWaitableQueue();
void TestOneProducerAndConsumer();
void TestOneProducerMultipleConsumers();
void TestMultipleProducersAndConsumers();

int main()
{
    BasicTestsWaitableQueue();
    TestOneProducerAndConsumer();
    TestOneProducerMultipleConsumers();
    TestMultipleProducersAndConsumers();

    PASS;

    return 0;
}

/*---------------------Threads functions implementations----------------------*/
void ProducerThread(TSWaitableQueue<int>& queue, size_t iterations, int seconds)
{
    int k = 1;

    for (size_t i = 0; i < iterations; ++i, ++k)
    {
        queue.Push(k);
        std::cout << "Pushed: " << k << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
}

void ConsumerBlockingThread(TSWaitableQueue<int>& queue, size_t iterations)
{
    int element = 0;

    for (size_t i = 0; i < iterations; ++i)
    {
        queue.Pop(element);
        std::cout << "Popped: " << element << std::endl;
    }
}

/*----------------------Tests functions implementations-----------------------*/
void BasicTestsWaitableQueue()
{
    size_t element;
    TSWaitableQueue<size_t> queue;
    
    queue.Push(4);
    TEST("IsEmpty check", queue.IsEmpty(), false);
    queue.Push(6);
    TEST("IsEmpty check", queue.IsEmpty(), false);

    queue.Pop(element, std::chrono::milliseconds(3000));
    // std::cout << "Popped: " << element << std::endl;
    TEST("non-blocking (timeout) pop check", element, 4);
    queue.Pop(element, std::chrono::milliseconds(3000));
    // std::cout << "Popped: " << element << std::endl;
    TEST("non-blocking (timeout) pop check", element, 6);

    TEST("failure of non-blocking pop", 
        queue.Pop(element, std::chrono::milliseconds(3000)), false);

    queue.Push(5);
    queue.Push(6);
    queue.Push(7);
    queue.Pop(element);
    TEST("blocking pop check", element, 5);
    queue.Pop(element);
    TEST("blocking pop check", element, 6);
    queue.Pop(element);
    TEST("blocking pop check", element, 7);

    TEST("IsEmpty check", queue.IsEmpty(), true);
}

void TestOneProducerAndConsumer()
{
    TSWaitableQueue<int> queue;
    const size_t iterations = 5;

    TEST("sanity check", queue.IsEmpty(), true);

    std::thread producer(ProducerThread, std::ref(queue), iterations, 2);
    std::thread consumer(ConsumerBlockingThread, std::ref(queue), iterations);

    producer.join();
    consumer.join();

    TEST("sanity check", queue.IsEmpty(), true);
}

void TestOneProducerMultipleConsumers()
{
    TSWaitableQueue<int> queue;
    const size_t iterations = 3;
    std::jthread consumers[iterations];
    std::jthread producer(ProducerThread, std::ref(queue), iterations, 1);
    
    for (size_t i = 0; i < iterations; ++i)
    {
        consumers[i] = std::jthread(ConsumerBlockingThread, std::ref(queue), 1);
    }
}

void TestMultipleProducersAndConsumers()
{
    TSWaitableQueue<int> queue;
    const size_t iterations = 4;
    std::jthread producers[iterations];
    std::jthread consumers[iterations];

    for (size_t i = 0; i < iterations; ++i)
    {
        producers[i] = std::jthread(ProducerThread, std::ref(queue), 1, 1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        consumers[i] = std::jthread(ConsumerBlockingThread, std::ref(queue), 1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // priority queue
    TSWaitableQueue<int, std::priority_queue<int> > pqueue;
    std::vector<int> numbers = { 6, 7, 2, 3, 9, 6 };

    for (int item : numbers)
    {
        pqueue.Push(item);
    }
}
/**
* @file: TSWaitableQueue.hpp
* @author: Ofir Nahshoni
* @brief: This is an API for the Thread-safe Waitable Queue. This header
* includes WaitableQueueDS.hpp, which contains Waitable Queues data 
* structures.
*/

#ifndef ILRD_RD1645_TS_WAITABLE_QUEUE_HPP
#define ILRD_RD1645_TS_WAITABLE_QUEUE_HPP

#include <mutex>                    // std::mutex
#include <condition_variable>       // std::condition_variable
#include <chrono>                   // std::chrono::milliseconds

#include "WaitableQueue.hpp"        // WaitableQueue<T, DS>

namespace ilrd
{

/**
 * @class: TSWaitableQueue<T, DS>
 * @brief: Defines a generic class for purpose.
 * @tparam T: Defines the type of element stored in the queue.
 * @tparam DS: Defines the Data Structure to use
 */
template <typename T, typename DS = std::queue<T>>
class TSWaitableQueue: private queue_details::WaitableQueue<T, DS>
{
public:
    TSWaitableQueue() = default;
    ~TSWaitableQueue() = default;
    void Push(const T& element);
    void Pop(T& outElement);
    bool Pop(T& outElement, std::chrono::milliseconds timeout);
    bool IsEmpty() const;

private:
    std::mutex m_mutex;
    std::condition_variable m_condVar;
};  // class TSWaitableQueue<T, DS>

template <typename T, typename DS>
void TSWaitableQueue<T, DS>::Push(const T& element)
{
    std::unique_lock lock(m_mutex);
    queue_details::WaitableQueue<T, DS>::Push(element);
    m_condVar.notify_one();
}

template <typename T, typename DS>
void TSWaitableQueue<T, DS>::Pop(T& outElement)
{
    std::unique_lock lock(m_mutex);
    m_condVar.wait(lock, [this] {
        return !queue_details::WaitableQueue<T, DS>::IsEmpty();
    });
    queue_details::WaitableQueue<T, DS>::Pop(outElement);
}

template <typename T, typename DS>
bool TSWaitableQueue<T, DS>::Pop(T& outElement, std::chrono::milliseconds timeout)
{
    std::unique_lock lock(m_mutex);
    if (!m_condVar.wait_for(lock, timeout, [this] {
        return !queue_details::WaitableQueue<T, DS>::IsEmpty();
    }))
    {
        return false;
    }

    queue_details::WaitableQueue<T, DS>::Pop(outElement);
    return true;
}

template <typename T, typename DS>
bool TSWaitableQueue<T, DS>::IsEmpty() const
{
    return queue_details::WaitableQueue<T, DS>::IsEmpty();
}

}   // namespace ilrd

#endif  // ILRD_RD1645_TS_WAITABLE_QUEUE_HPP
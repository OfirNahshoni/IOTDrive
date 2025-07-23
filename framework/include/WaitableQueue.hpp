/**
* @file: WaitableQueueDS.hpp
* @author: Ofir Nahshoni
* @brief: This is an API for Waitable Queue data structure. It contains
* generic (template) classes that follow the following ADT:
* void push(void* data);
* void* pop();
* bool empty();
* The first template is the general template of generic Queue, default is
* std::queue<T>, to provide FIFO behavior.
* The second template is the partial template class that based on
* std::priority_queue<T>, to provide not only FIFO, but also Priority order.
*/

#include <queue>        // std::queue, std::priority_queue

namespace queue_details
{

/**
* @class: WaitableQueue<T, DS>
* @tparam T: The type of the elements that would be stored in the Queue
* @tparam DS: The data structure, that has queue-like ADT
*/
template <typename  T, typename DS = std::queue<T>>
class WaitableQueue
{
protected:
    WaitableQueue() = default;
    ~WaitableQueue() = default;
    void Push(const T& element);
    void Pop(T& outElement);
    bool IsEmpty() const;

private:
    DS m_queue;
    WaitableQueue(const WaitableQueue& other) = delete;
    WaitableQueue<T, DS>& operator=(const WaitableQueue& rhs) = delete;
};  // class WaitableQueue<T, DS>

/**
* @class: WaitableQueue<T, DS>
* @brief: Defines a partial specialized generic class for std::priority_queue.
* @tparam T: The type of the elements that would be stored in the Priority Queue
*/
template <typename T>
class WaitableQueue<T, std::priority_queue<T>>
{
protected:
    WaitableQueue() = default;
    ~WaitableQueue() = default;
    void Push(const T& element);
    void Pop(T& outElement);
    bool IsEmpty() const;

private:
    std::priority_queue<T> m_pqueue;
    WaitableQueue(const WaitableQueue& other) = delete;
    WaitableQueue<T, std::priority_queue<T>>& operator=(const WaitableQueue& rhs) = delete;
};  // class WaitableQueue<T, std::priority_queue<T>>

/*----------------------------General Template--------------------------------*/
template <typename T, typename DS>
void WaitableQueue<T, DS>::Push(const T& element)
{
    m_queue.push(element);
}

template <typename T, typename DS>
void WaitableQueue<T, DS>::Pop(T& outElement)
{
    outElement = m_queue.front();
    m_queue.pop();
}

template <typename T, typename DS>
bool WaitableQueue<T, DS>::IsEmpty() const
{
    return m_queue.empty();
}

/*-----------------------Partial Specialized Template-------------------------*/
template <typename T>
void WaitableQueue<T, std::priority_queue<T>>::Push(const T& element)
{
    m_pqueue.push(element);
}

template <typename T>
void WaitableQueue<T, std::priority_queue<T>>::Pop(T& outElement)
{
    outElement = m_pqueue.top();
    m_pqueue.pop();
}

template <typename T>
bool WaitableQueue<T, std::priority_queue<T>>::IsEmpty() const
{
    return m_pqueue.empty();
}

}   // namespace queue_details
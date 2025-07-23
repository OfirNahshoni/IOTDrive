/**
* @file: Singleton.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that encapsulates the creation of an object.
* @reviewer: Ofir1st
* @status: APPROVED
*/

#ifndef ILRD_RD1645_SINGLETON_HPP
#define ILRD_RD1645_SINGLETON_HPP

#include <mutex>        // std::mutex
#include <atomic>       // std::atomic

namespace ilrd
{

template <typename T>
class Singleton
{
public:
    static T* GetInstance();

private:
    static std::mutex m_mutex;
    static std::atomic<T*> m_instance;
    static std::atomic_bool m_isDestroyed;

    Singleton() = default;
    ~Singleton() = default;
    static void DeleteAtExit();
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& rhs) = delete;
};  // class Singleton

template <typename T>
std::mutex Singleton<T>::m_mutex;

template <typename T>
std::atomic<T*> Singleton<T>::m_instance = nullptr;

template <typename T>
std::atomic_bool Singleton<T>::m_isDestroyed = false;

// Phase A
template <typename T>
T* Singleton<T>::GetInstance()
{
    if (m_isDestroyed.load())
    {
        throw std::runtime_error("singleton is already destroyed");
    }

    T* temp = m_instance.load(std::memory_order_acquire);

    if (!temp)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        temp = m_instance.load(std::memory_order_relaxed);

        if (!temp)
        {
            m_instance.store(new T, std::memory_order_release);
            temp = m_instance.load(std::memory_order_relaxed);
            atexit(DeleteAtExit);
        }
    }

    return temp;
}

template <typename T>
void Singleton<T>::DeleteAtExit()
{
    m_isDestroyed.store(true);
    delete m_instance.load(std::memory_order_acquire);
    m_instance.store(nullptr, std::memory_order_release);
}

} // namespace ilrd

#endif  // ILRD_RD1645_SINGLETON_HPP
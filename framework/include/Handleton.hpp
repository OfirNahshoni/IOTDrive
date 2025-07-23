/**
* @file: Handleton.hpp
* @author: Ofir Nahshoni.
* @reviewer: Amit
* @status: APPROVED
* @brief: This is a header file that defines the Handleton API. It's almost
* identical to Singleton, but has an unordered map that can create different
* types on the same Handleton.
*/

#ifndef ILRD_RD1645_HANDLETON_HPP
#define ILRD_RD1645_HANDLETON_HPP

#include <mutex>                // std::mutex
#include <unordered_map>        // std::unordered_map
#include <memory>               // std::unique_ptr, std::shared_ptr

namespace ilrd
{

class Handleton
{
public:
    template <typename T>
    static T* GetInstance();
    
private:
    class HashFunc
    {
    public:
        size_t operator()(const std::type_info* typeInfo) const
        {
            return typeInfo->hash_code();
        }
    };

    class Comparator
    {
    public:
        bool operator()(const std::type_info* lhs, const std::type_info* rhs) const
        {
            return (*lhs == *rhs);
        }
    };

    static std::mutex m_mutex;
    static std::unordered_map<const std::type_info*, std::shared_ptr<void>, 
                                                HashFunc, Comparator> m_symbols;

    explicit Handleton() = default;
    Handleton(const Handleton& other) = delete;
    Handleton& operator=(const Handleton& rhs) = delete;
};  // class Handleton

template <typename T>
T* Handleton::GetInstance()
{
    static std::once_flag flag;

    std::call_once(flag, []() {
        std::unique_lock lock(m_mutex);

        if (!m_symbols.contains(&typeid(T)))
        {
            m_symbols[&typeid(T)].reset(new T);
        }
    });
    
    return static_cast<T*>(m_symbols[&typeid(T)].get());
}
    
}   // namespace ilrd

#endif  // ILRD_RD1645_HANDLETON_HPP
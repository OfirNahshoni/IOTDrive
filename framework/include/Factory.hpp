/**
* @file: Factory.hpp
* @author: Ofir Nahshoni
* @brief: This is an API template class that automates the Factory 
* functionality.
* @reviewer: Alon
* @status: APPROVED
*/

#ifndef ILRD_RD1645_FACTORY_HPP
#define ILRD_RD1645_FACTORY_HPP

#include <functional>           // std::function
#include <memory>               // std::shared_ptr
#include <unordered_map>        // std::unordered_map

namespace ilrd
{

template <typename KEY, typename BASE, typename ...ARGS>
class Factory
{
public:
    friend class Handleton;

    std::shared_ptr<BASE> Create(KEY key, ARGS... args);
    void Register(KEY key, std::function<std::shared_ptr<BASE>(ARGS...)> func);
    
private:
    std::unordered_map<KEY, std::function<std::shared_ptr<BASE>(ARGS...)>> 
                                                                m_creatorsMap;
                                                                
    explicit Factory() = default;
    Factory(const Factory& other) = delete;
    Factory& operator=(const Factory& rhs) = delete;
};  // class Factory

template <typename KEY, typename BASE, typename... ARGS>
void Factory<KEY, BASE, ARGS...>::Register(KEY key, 
                            std::function<std::shared_ptr<BASE>(ARGS...)> func)
{
    m_creatorsMap[key] = func;
}

template <typename KEY, typename BASE, typename... ARGS>
std::shared_ptr<BASE> Factory<KEY, BASE, ARGS...>::Create(KEY key, ARGS... args)
{
    return m_creatorsMap.at(key)(args...);
}

}   // namespace ilrd

#endif  // ILRD_RD1645_FACTORY_HPP
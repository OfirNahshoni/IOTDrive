/** 
* @file: DispatchCallback.hpp
* @author: Ofir Nahshoni
* @brief: This is an API header file that contains class templates, according
* to the Dispatcher Design-Pattern.
* @reviewer: Itai
* @status: APPROVED
*/

#ifndef ILRD_RD1645_DISPATCH_CALLBACK_HPP
#define ILRD_RD1645_DISPATCH_CALLBACK_HPP

#include <list>         // std::list
#include <queue>        // std::queue<T>

namespace ilrd
{

template <typename Event> class Dispatcher;

template <typename Event>
class ACallback
{
public:
    virtual void NotifyDeath();
    virtual void Notify(Event event) = 0;
    virtual void SetDispatcher(Dispatcher<Event>* dispatcher);

protected:
    ACallback() = default;
    virtual ~ACallback();

private:
    Dispatcher<Event>* m_dispatcher;
};  // class ACallback<Event>

template <typename Event>
ACallback<Event>::~ACallback()
{
    if (m_dispatcher)
    {
        m_dispatcher->Unregister(this);
    }
}

template <typename Event>
void ACallback<Event>::NotifyDeath()
{ }

template <typename Event>
void ACallback<Event>::SetDispatcher(Dispatcher<Event>* dispatcher)
{
    m_dispatcher = dispatcher;
}

template <typename Event, typename Object>
class Callback : public ACallback<Event>
{
public:
    Callback(Object& object, void(Object::*mNotify)(Event),
            void(Object::*mNotifyDeath)() = nullptr);
    void Notify(Event event);
    void NotifyDeath();

private:
    Object& m_object;
    void(Object::*m_notify)(Event);
    void(Object::*m_notifyDeath)();
};  // class Callback<Event, Object>

template <typename Event, typename Object>
Callback<Event, Object>::Callback(Object& object, void(Object::*mNotify)(Event),
                            void(Object::*mNotifyDeath)()):
                            m_object(object), 
                            m_notify(mNotify), 
                            m_notifyDeath(mNotifyDeath)
{ }

template <typename Event, typename Object>
void Callback<Event, Object>::Notify(Event event)
{
    (m_object.*m_notify)(event);
}

template <typename Event, typename Object>
void Callback<Event, Object>::NotifyDeath()
{
    if (m_notifyDeath)
    {
        (m_object.*m_notifyDeath)();
    }
}


/**
* @class: Dispatcher
* @brief: Defines a generic class for Dispatcher DP - which registers or
* unregisters callback functions.
* @tparam Event: Defines the type of the argument, that needs to be passed to
* the notified function.
*/
template <typename Event>
class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher();
    void Notify(Event event);
    void Register(ACallback<Event>* callback);
    void Unregister(ACallback<Event>* callback);

private:
    enum Operation
    {
        REGISTER,
        UNREGISTER,
        NUM_OF_OPERATIONS
    };

    std::list<ACallback<Event>*> m_callbackList;
    std::queue<std::pair<Operation, ACallback<Event>*>> m_opsQueue;

    void ExecuteOperationsFromQueue();
};  // class Dispatcher<Event>

template <typename Event>
Dispatcher<Event>::~Dispatcher()
{
    ExecuteOperationsFromQueue();

    for (auto cb : m_callbackList) 
    {
        cb->SetDispatcher(nullptr);
        cb->NotifyDeath();
    }
}

template <typename Event>
void Dispatcher<Event>::Notify(Event event)
{
    ExecuteOperationsFromQueue();

    for (auto cb : m_callbackList) 
    {
        cb->Notify(event);
    }
}

template <typename Event>
void Dispatcher<Event>::Register(ACallback<Event>* callback)
{
    m_opsQueue.push(std::make_pair(REGISTER, callback));
}

template <typename Event>
void Dispatcher<Event>::Unregister(ACallback<Event>* callback)
{
    m_opsQueue.push(std::make_pair(UNREGISTER, callback));
}

template <typename Event>
void Dispatcher<Event>::ExecuteOperationsFromQueue()
{
    while (!m_opsQueue.empty())
    {
        std::pair<Operation, ACallback<Event>*> element = m_opsQueue.front();

        if (element.first == REGISTER)
        {
            element.second->SetDispatcher(this);
            m_callbackList.push_back(element.second);
        }
        else if (element.first == UNREGISTER)
        {
            element.second->SetDispatcher(nullptr);
            m_callbackList.remove(element.second);
        }

        m_opsQueue.pop();
    }
}

}   // namespace ilrd

#endif  // ILRD_RD1645_DISPATCH_CALLBACK_HPP
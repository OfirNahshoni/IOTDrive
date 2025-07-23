/**
* @file: Framework.cpp
* @author: Ofir Nahshoni
* @reviewer: Gil
* @status: 
* @brief: This is a source file that implements the Framework API.
*/

#include "Factory.hpp"          // ilrd::Factory
#include "Reactor.hpp"          // ilrd::Reactor
#include "FWTPTask.hpp"         // ilrd::FWTPTask
#include "Framework.hpp"        // ilrd::Framework
#include "Handleton.hpp"        // ilrd::Handleton
#include "ThreadPool.hpp"       // ilrd::ThreadPool

ilrd::Framework::Framework(const INPUTS_VECTOR& inputVec, 
                            const FACTORY_VEC_TYPE& factoryVec,
                            const char* pluginsPath) : 
        m_loader(),
        m_monitor(pluginsPath),
        m_loadCB(std::make_shared<Callback<const std::string&, DllLoader>>(
                m_loader, &DllLoader::Load)),
        m_unloadCB(std::make_shared<Callback<const std::string&, DllLoader>>(
                    m_loader, &DllLoader::UnLoad))
{
    for (const auto& [keyPair, func] : inputVec)
    {
        Handleton::GetInstance<Reactor>()->Register(keyPair.first, 
            keyPair.second, [func](int fd, Mode mode) {
                std::shared_ptr<ITaskArgs> ptrArgs = func->GetTaskArgs(fd, mode);

                if (!ptrArgs)
                {
                    return;
                }

                Handleton::GetInstance<threadpool::ThreadPool>()->AddTask(
                                        std::make_shared<FWTPTask>(ptrArgs));
            });
    }

    for (const auto& [key, func] : factoryVec)
    {
        ilrd::Handleton::GetInstance<ilrd::Factory<int, ICommand, 
                                    ilrd::ITaskArgs*>>()->Register(key, func);
    }

    m_monitor.RegisterLoad(m_loadCB.get());
    m_monitor.RegisterUnload(m_unloadCB.get());
}

void ilrd::Framework::Run()
{
    m_monitor.Run();
    Handleton::GetInstance<Reactor>()->Run();
}

void ilrd::Framework::Stop()
{
    ilrd::Handleton::GetInstance<Reactor>()->Stop();
}
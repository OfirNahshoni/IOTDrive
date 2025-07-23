#include "Factory.hpp"              // ilrd::Factory
#include "FWTPTask.hpp"             // ilrd::FWTPTask
#include "ICommand.hpp"             // ilrd::ICommand
#include "Logger.hpp"               // ilrd::Logger
#include "AsyncInjection.hpp"       // ilrd::AsyncInjection

ilrd::FWTPTask::FWTPTask(std::shared_ptr<ITaskArgs> ptrTaskArgs) : 
                        m_ptrTaskArgs()
{
    m_ptrTaskArgs.swap(ptrTaskArgs);
}

void ilrd::FWTPTask::Run()
{
    try
    {
        std::shared_ptr<ICommand> ptrCmd = Handleton::GetInstance<Factory<int, 
                    ICommand, ITaskArgs*>>()->Create(m_ptrTaskArgs->GetKey(), 
                    m_ptrTaskArgs.get());
        const auto return_val = ptrCmd->
                                            Execute(m_ptrTaskArgs.get());

        if (return_val.has_value())
        {
            new AsyncInjection(return_val->first, return_val->second);
        }
    }
    catch (...)
    {
        Handleton::GetInstance<Logger>()->Log("failed in Factory::Create()");
    }
}
/**
* @file: Framework.hpp
* @author: Ofir Nahshoni
* @reviewer: Gil
* @status: 
* @brief: This is a header for the Framework API, part of the final project.
*/

#ifndef ILRD_RD1645_FRAMEWORK_HPP
#define ILRD_RD1645_FRAMEWORK_HPP

#include <vector>               // std::vector
#include <string>               // std::string
#include <memory>               // std::shared_ptr

#include "IInputProxy.hpp"      // ilrd::Mode
#include "ICommand.hpp"         // ilrd::ICommand
#include "DllLoader.hpp"        // ilrd::DllLoader
#include "DirMonitor.hpp"       // ilrd::DirMonitor

namespace ilrd
{

class Framework
{
public:
    using INPUTS_VECTOR = std::vector<std::pair<std::pair<int, Mode>, 
                                                std::shared_ptr<IInputProxy>>>;
    using FACTORY_VEC_TYPE = std::vector<std::pair<int, 
                        std::function<std::shared_ptr<ICommand>(ITaskArgs*)>>>;
    using CALLBACK_TYPE = std::shared_ptr<Callback<const std::string&,
                                                                    DllLoader>>;

    Framework(const INPUTS_VECTOR& inputVec, const FACTORY_VEC_TYPE& factoryVec, 
                                        const char* pluginsPath = "./plugins/");
    ~Framework() = default;
    void Run();
    void Stop();
    
private:
    DllLoader m_loader;
    DirMonitor m_monitor;
    CALLBACK_TYPE m_loadCB;
    CALLBACK_TYPE m_unloadCB;
};  // class Framework

}   // namespace ilrd

#endif  // ILRD_RD1645_FRAMEWORK_HPP
/**
* @file: TestDirMonitor.cpp
* @author: Ofir Nahshoni
* @brief: This file tests DirMonitor and DllLoader APIs.
*/

#include <iostream>             // std::cout
#include <memory>               // std::shared_ptr
#include <chrono>               // std::chrono::seconds

#include "DllLoader.hpp"        // DllLoader
#include "DirMonitor.hpp"       // DirMonitor

void TestForLoadingLibsAtRuntime();

int main()
{
    TestForLoadingLibsAtRuntime();

    return 0;
}

void TestForLoadingLibsAtRuntime()
{
    std::string dir = "../../../framework/test/plugins/";
    ilrd::DirMonitor monitor(dir);
    ilrd::DllLoader loader;

    std::shared_ptr<ilrd::Callback<const std::string&, ilrd::DllLoader>> load = 
        std::make_shared<ilrd::Callback<const std::string&, ilrd::DllLoader>>(
        loader, &ilrd::DllLoader::Load);

    std::shared_ptr<ilrd::Callback<const std::string&, ilrd::DllLoader>> unload =
        std::make_shared<ilrd::Callback<const std::string&, ilrd::DllLoader>>(
        loader, &ilrd::DllLoader::UnLoad);
    
    monitor.RegisterLoad(load.get());
    monitor.RegisterUnload(unload.get());
    monitor.Run();

    std::cout << "Monitoring plugins directory (30 seconds)" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "Bye Bye" << std::endl;
}
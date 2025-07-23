/**
* @file: DllLoader.cpp
* @author: Ofir Nahshoni
* @brief: This source file implements the API functions of DllLoader.hpp.
* @reviewer: Gil
* @status: APPROVED
*/

#include <iostream>     // std::cerr
#include <dlfcn.h>      // dlopen, dlclose

#include "DllLoader.hpp"

ilrd::DllLoader::~DllLoader()
{
    for (const auto& [str, handle] : m_libsMap)
    {
        dlclose(handle);
    }
}

void ilrd::DllLoader::Load(const std::string& pathname)
{
    void* handle = dlopen(pathname.c_str(), RTLD_LAZY);

    if (!handle)
    {
        std::cerr << "[DllLoader] dlopen() failed for: " << pathname << std::endl;
        std::cerr << "[DllLoader] dlerror(): " << dlerror() << std::endl;
        throw std::runtime_error("failed to open with dlopen()");
    }

    m_libsMap.emplace(pathname, handle);
}

void ilrd::DllLoader::UnLoad(const std::string& pathname)
{
    if (m_libsMap.find(pathname) == m_libsMap.end())
    {
        throw std::runtime_error("double dlclose() error");
    }
    
    dlclose(m_libsMap[pathname]);
    m_libsMap.erase(pathname);
}
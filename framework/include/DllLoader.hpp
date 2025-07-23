/**
* @file: DllLoader.hpp
* @author: Ofir Nahshoni
* @brief: This header file defines the API of a DllLoader.
* @reviewer: Shani
* @status: APPROVED
*/

#ifndef ILRD_RD1645_DLL_LOADER_HPP
#define ILRD_RD1645_DLL_LOADER_HPP

#include <string>           // std::string
#include <unordered_map>    // std::unordered_map

namespace ilrd
{

class DllLoader
{
public:
    DllLoader() = default;
    ~DllLoader();
    void Load(const std::string& pathname);
    void UnLoad(const std::string& pathname);

private:
    typedef void* handleDll;
    std::unordered_map<std::string, handleDll> m_libsMap;
};  // class DllLoader

}   // namespace ilrd

#endif  // ILRD_RD1645_DLL_LOADER_HPP
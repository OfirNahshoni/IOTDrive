/**
* @file: FileManager.hpp
* @author: Ofir Nahshoni
* @brief: This is a header that defines the API of FileManager, which
* implements the interface IFileManager.
*/

#ifndef ILRD_RD1645_FILE_MANAGER_HPP
#define ILRD_RD1645_FILE_MANAGER_HPP

#include <mutex>                // std::mutex
#include <fstream>              // std::fstream

#include "IFileManager.hpp"

namespace ilrd
{

class FileManager : public IFileManager
{
public:
    friend class Handleton;
    void Init(const std::string& path);
    bool Read(size_t offset, size_t length, char* outBuffer);
    bool Write(size_t offset, size_t length, std::shared_ptr<char[]> buffer);
    
private:
    std::fstream m_fs;
    std::mutex m_mutex;
    
    FileManager() = default;
};  // class FileManager

}   // namespace ilrd

#endif  // ILRD_RD1645_FILE_MANAGER_HPP
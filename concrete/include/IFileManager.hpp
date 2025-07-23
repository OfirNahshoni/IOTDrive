/**
* @file: IFileManager.hpp
* @author: Ofir Nahshoni
* @brief: This is a header that defines the interface for a file manager,
* which includes 2 operations: Read() and Write().
*/

#ifndef ILRD_RD1645_IFILE_MANAGER_HPP
#define ILRD_RD1645_IFILE_MANAGER_HPP

#include <cstddef>          // size_t
#include <memory>           // std::shared_ptr

namespace ilrd
{

class IFileManager
{
public:
    virtual bool Read(size_t offset, size_t length, char* outBuffer) = 0;
    virtual bool Write(size_t offset, size_t length, 
                                            std::shared_ptr<char[]> buffer) = 0;
};  // class IFileManager

}   // namespace ilrd

#endif  // ILRD_RD1645_IFILE_MANAGER_HPP
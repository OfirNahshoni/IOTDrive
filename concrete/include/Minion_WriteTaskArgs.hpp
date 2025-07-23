/**
* @file: Minion_WriteTaskArgs.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the API for WriteTaskArgs for the
* Minion. early version the minion is just a local process in the same machine,
* and at final stage it will be a process in the Raspberry PI.
*/

#ifndef MINION_WRITE_TASK_ARGS_HPP
#define MINION_WRITE_TASK_ARGS_HPP

#include <cstddef>          // size_t
#include <memory>           // std::shared_ptr

#include "UID.hpp"
#include "ITaskArgs.hpp"

namespace ilrd
{

class Minion_WriteTaskArgs : public ITaskArgs
{
public:
    Minion_WriteTaskArgs(const UID& uid, size_t offset, size_t length, 
                                                std::shared_ptr<char[]> buffer);
    int GetKey() const;
    const UID& GetUID() const;
    size_t GetOffset() const;
    size_t GetLength() const;
    std::shared_ptr<char[]> GetBuffer() const;

private:
    UID m_uid;
    size_t m_offset;
    size_t m_length;
    std::shared_ptr<char[]> m_buffer;
};  // class Minion_WriteTaskArgs

}   // namespace ilrd

#endif  // MINION_WRITE_TASK_ARGS_HPP
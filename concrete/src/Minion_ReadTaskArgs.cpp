/**
* @file: Minion_ReadTaskArgs.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of ReadTaskArgs for
* a Minion. it's used in Minion_ReadCommand in order to get the args for an
* operation to do with the FileManager (only the Minion_ReadCommand uses
* the FileManager class).
*/

#include "Minion_ReadTaskArgs.hpp"

ilrd::Minion_ReadTaskArgs::Minion_ReadTaskArgs(const UID& uid, size_t offset, 
                                            size_t length,
                                            std::shared_ptr<char[]> buffer) :
                                            m_uid(uid),
                                            m_offset(offset),
                                            m_length(length),
                                            m_buffer(buffer)
{ }

int ilrd::Minion_ReadTaskArgs::GetKey() const
{
    return 0;
}

const ilrd::UID& ilrd::Minion_ReadTaskArgs::GetUID() const
{
    return m_uid;
}

size_t ilrd::Minion_ReadTaskArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::Minion_ReadTaskArgs::GetLength() const
{
    return m_length;
}

std::shared_ptr<char[]> ilrd::Minion_ReadTaskArgs::GetBuffer() const
{
    return m_buffer;
}
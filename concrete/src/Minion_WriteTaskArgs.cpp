/**
* @file: Minion_WriteTaskArgs.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of WriteTaskArgs for
* a Minion. it's used in Minion_WriteCommand in order to get the args for an
* operation to do with the FileManager.
*/

#include "Minion_WriteTaskArgs.hpp"

ilrd::Minion_WriteTaskArgs::Minion_WriteTaskArgs(const UID& uid, size_t offset, 
                                size_t length, std::shared_ptr<char[]> buffer) :
                                m_uid(uid),
                                m_offset(offset),
                                m_length(length),
                                m_buffer(buffer)
{ }

int ilrd::Minion_WriteTaskArgs::GetKey() const
{
    return 1;
}

const ilrd::UID& ilrd::Minion_WriteTaskArgs::GetUID() const
{
    return m_uid;
}

size_t ilrd::Minion_WriteTaskArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::Minion_WriteTaskArgs::GetLength() const
{
    return m_length;
}

std::shared_ptr<char[]> ilrd::Minion_WriteTaskArgs::GetBuffer() const
{
    return m_buffer;
}
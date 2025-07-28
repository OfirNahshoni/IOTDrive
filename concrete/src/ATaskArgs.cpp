/**
* @file: ATaskArgs.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the class API ATaskArgs.
*/

#include "ATaskArgs.hpp"    // ilrd::ATaskArgs
#include "Logger.hpp"       // ilrd::Log() with Handleton

ilrd::ATaskArgs::ATaskArgs() : m_uid()
{ }

ilrd::UID ilrd::ATaskArgs::GetUID() const
{
    return m_uid;
}

ilrd::ReadArgs::ReadArgs(const NBDArgs& args) : m_offset(args.m_offset),
                                                m_length(args.m_length),
                                                m_buffer(args.m_buffer)
{ }

int ilrd::ReadArgs::GetKey() const
{
    return 0;
}

size_t ilrd::ReadArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::ReadArgs::GetLength() const
{
    return m_length;
}

std::shared_ptr<char[]> ilrd::ReadArgs::GetBuffer() const
{
    return m_buffer;
}

ilrd::WriteArgs::WriteArgs(const NBDArgs& args) : m_offset(args.m_offset),
                                                m_length(args.m_length),
                                                m_buffer(args.m_buffer)
{ }

int ilrd::WriteArgs::GetKey() const
{
    return 1;
}

size_t ilrd::WriteArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::WriteArgs::GetLength() const
{
    return m_length;
}

std::shared_ptr<char[]> ilrd::WriteArgs::GetBuffer() const
{
    return m_buffer;
}
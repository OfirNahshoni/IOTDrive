/**
* @file: UID.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of UID - a wrapper
* class of C API ilrd_uid.h.
*/

#include <stdexcept>

#include "UID.hpp"

size_t ilrd::UID::m_counter = 0;

ilrd::UID::UID() : m_id(++m_counter)
{ }

ilrd::UID::UID(const UID& other) : m_id(other.m_id)
{ }

size_t ilrd::UID::GetID() const
{
    return m_id;
}

ilrd::UID &ilrd::UID::operator=(const UID& rhs)
{
    if (this != &rhs)
    {
        m_id = rhs.m_id;
    }

    return *this;
}

bool ilrd::operator<(const UID& lhs, const UID& rhs)
{
    return (lhs.GetID() < rhs.GetID());
}

bool ilrd::operator==(const UID& lhs, const UID& rhs)
{
    return (lhs.GetID() == rhs.GetID());
}
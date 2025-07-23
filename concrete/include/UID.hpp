/**
* @file: UID.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines an API that wraps around 
* ilrd_uid_t.
*/

#ifndef ILRD_RD1645_UID_HPP
#define ILRD_RD1645_UID_HPP

namespace ilrd
{

class UID
{
public:
    UID();
    UID(const UID& other);
    size_t GetID() const;
    UID& operator=(const UID& rhs);
    friend bool operator<(const UID& lhs, const UID& rhs);
    friend bool operator==(const UID& lhs, const UID& rhs);

private:
    size_t m_id;
    static size_t m_counter;
};  // class UID

bool operator<(const UID& lhs, const UID& rhs);
bool operator==(const UID& lhs, const UID& rhs);

}   // namespace ilrd

#endif  // ILRD_RD1645_UID_HPP
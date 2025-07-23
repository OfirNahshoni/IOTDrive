/**
* @file: ATaskArgs.hpp
* @author: Ofir Nahshoni
* @brief: This is an abstract class ATaskArgs, which decouples the ITaskArgs
* with the rest of the system. add a UID to the Args.
*/

#ifndef ILRD_RD1645_ATASK_ARGS_HPP
#define ILRD_RD1645_ATASK_ARGS_HPP

#include "UID.hpp"
#include "ITaskArgs.hpp"    // ilrd::ITaskArgs

namespace ilrd
{

enum ArgsType
{
    AREAD = 0,
    AWRITE = 1
};

struct NBDArgs
{
    size_t m_offset;
    size_t m_length;
    std::shared_ptr<char[]> m_buffer;
};

class ATaskArgs : public ITaskArgs
{
public:
    ATaskArgs();
    UID GetUID() const;

private:
    UID m_uid;
};  // class ATaskArgs

class ReadArgs : public ATaskArgs
{
public:
    ReadArgs(const NBDArgs& args);
    int GetKey() const;

    // debug
    size_t GetOffset() const;
    size_t GetLength() const;
    std::shared_ptr<char[]> GetBuffer() const;

private:
    size_t m_offset;
    size_t m_length;
    std::shared_ptr<char[]> m_buffer;
};  // class ReadArgs

class WriteArgs : public ATaskArgs
{
public:
    WriteArgs(const NBDArgs& args);
    int GetKey() const;

    // debug
    size_t GetOffset() const;
    size_t GetLength() const;
    std::shared_ptr<char[]> GetBuffer() const;

private:
    size_t m_offset;
    size_t m_length;
    std::shared_ptr<char[]> m_buffer;
};  // class ReadArgs

}   // namespace ilrd

#endif  // ILRD_RD1645_ATASK_ARGS_HPP
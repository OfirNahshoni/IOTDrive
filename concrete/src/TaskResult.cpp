/**
* @file: TaskResult.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the TaskResult API. It's
* responsible for holding the results from the messages that returned from
* the Minions.
*/

#include "TaskResult.hpp"

ilrd::TaskResult::TaskResult(bool status, TaskType taskType, const UID& uid,
                            size_t length, std::shared_ptr<char[]> buffer) : 
                            m_uid(uid),
                            m_status(status), 
                            m_length(length),
                            m_taskType(taskType), 
                            m_buffer(buffer)
{ }

ilrd::UID ilrd::TaskResult::GetUid() const
{
    return m_uid;
}

bool ilrd::TaskResult::GetStatus() const
{
    return m_status;
}

ilrd::TaskResult::TaskType ilrd::TaskResult::GetTaskType() const
{
    return m_taskType;
}

std::shared_ptr<char[]> ilrd::TaskResult::GetBuffer() const
{
    return m_buffer;
}

size_t ilrd::TaskResult::GetLength() const
{
    return m_length;
}
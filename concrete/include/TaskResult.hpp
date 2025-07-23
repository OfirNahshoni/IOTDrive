/**
* @file: TaskResult.hpp
* @author: Ofir Nahshoni
* @brief: This is a header that defines an API of TaskResult. This class is
* responsible to hold the final status and important fields of a Ticket.
*/

#ifndef ILRD_RD1645_TASK_RESULT_HPP
#define ILRD_RD1645_TASK_RESULT_HPP

#include <memory>       // std::shared_ptr

#include "UID.hpp"      // ilrd::UID

namespace ilrd
{

class TaskResult
{
public:
    enum TaskType
    {
        RES_READ = 0,
        RES_WRITE = 1
    };

    TaskResult(bool status, TaskType type, const UID& uid, size_t length,
                std::shared_ptr<char[]> buffer = nullptr);
    ~TaskResult() = default;
    
    UID GetUid() const;
    bool GetStatus() const;
    size_t GetLength() const;
    TaskType GetTaskType() const;
    std::shared_ptr<char[]> GetBuffer() const;

private:
    UID m_uid;
    bool m_status;
    size_t m_length;
    TaskType m_taskType;
    std::shared_ptr<char[]> m_buffer;
};  // class TaskResult

}   // namespace ilrd

#endif  // ILRD_RD1645_TASK_RESULT_HPP
/**
* @file: ISchedulerTask.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the interface for tasks to be 
* scheduled by a scheduler (Scheduler.hpp).
* @reviewer: Zack
* @status: APPROVED
*/

#ifndef ILRD_RD1645_ISCHEDULER_TASK_HPP
#define ILRD_RD1645_ISCHEDULER_TASK_HPP

namespace ilrd
{

class ISchedulerTask
{
public:
    virtual void Execute() = 0;
};  // class ISchedulerTask

}   // namespace ilrd

#endif  // ILRD_RD1645_ISCHEDULER_HPP
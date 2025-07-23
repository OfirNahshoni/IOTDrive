/**
* @file: IResponse.hpp
* @author: Ofir Nahshoni
* @brief: This is an interface that responsible to wrap the ATaskArgs, with a
* generic class that decouple the the ResponseManager and MinionManager from
* the ITaskArgs interface.
*/

#ifndef ILRD_RD1645_IRESPONSE_HPP
#define ILRD_RD1645_IRESPONSE_HPP

#include "TaskResult.hpp"           // ilrd::TaskResult

namespace ilrd
{

class IResponse
{
public:
    virtual void OnSuccess(const TaskResult& taskResult) = 0;
    virtual void OnFailure(const TaskResult& taskResult) = 0;
};  // class IResponse

}   // namespace ilrd

#endif  // ILRD_RD1645_IRESPONSE_HPP
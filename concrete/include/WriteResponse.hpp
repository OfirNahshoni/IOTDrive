/**
* @file: WriteResponse.hpp
* @author: Ofir Nahshoni
* @brief: This is a concrete Response object that implements the interface
* IResponse.
*/

#ifndef ILRD_RD1645_WRITE_RESPONSE_HPP
#define ILRD_RD1645_WRITE_RESPONSE_HPP

#include "IResponse.hpp"        // ilrd::IResponse

namespace ilrd
{

class WriteResponse : public IResponse
{
public:
    WriteResponse() = default;
    ~WriteResponse() = default;
    void OnSuccess(const TaskResult& taskResult);
    void OnFailure(const TaskResult& taskResult);
};  // class Response

}   // namespace ilrd

#endif  // ILRD_RD1645_RESPONSE_HPP
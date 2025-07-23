/**
* @file: ReadResponse.hpp
* @author: Ofir Nahshoni
* @brief: This is a concrete Response object that implements the interface
* IResponse.
*/

#ifndef ILRD_RD1645_READ_RESPONSE_HPP
#define ILRD_RD1645_READ_RESPONSE_HPP

#include "IResponse.hpp"        // ilrd::IResponse

namespace ilrd
{

class ReadResponse : public IResponse
{
public:
    ReadResponse() = default;
    ~ReadResponse() = default;
    void OnSuccess(const TaskResult& taskResult);
    void OnFailure(const TaskResult& taskResult);
};  // class Response

}   // namespace ilrd

#endif  // ILRD_RD1645_RESPONSE_HPP
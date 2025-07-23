/**
* @file: ReadResponse.cpp
* @author: Ofir Nahshoni
* @brief: 
*/

#include <iostream>

#include "NBDProxy.hpp"
#include "Handleton.hpp"
#include "ReadResponse.hpp"

void ilrd::ReadResponse::OnSuccess(const TaskResult& taskResult)
{
    Handleton::GetInstance<NBDProxy>()->RespondToReadNBD(taskResult.GetUid(), 
                                                        true, 
                                                        taskResult.GetLength(),
                                                        taskResult.GetBuffer());
    std::cout << "SUCCESS Read, uid = " << taskResult.GetUid().GetID() << 
                                                                    std::endl;
}

void ilrd::ReadResponse::OnFailure(const TaskResult& taskResult)
{
    Handleton::GetInstance<NBDProxy>()->RespondToReadNBD(taskResult.GetUid(),
                                                        false,
                                                        taskResult.GetLength(),
                                                        taskResult.GetBuffer());
    std::cout << "FAILURE Read, uid = " << taskResult.GetUid().GetID() << 
                                                                    std::endl;
}
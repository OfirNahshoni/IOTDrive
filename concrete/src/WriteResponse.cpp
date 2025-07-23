/**
* @file: WriteResponse.cpp
* @author: Ofir Nahshoni
* @brief: 
*/

#include <iostream>

#include "NBDProxy.hpp"
#include "Handleton.hpp"
#include "WriteResponse.hpp"

void ilrd::WriteResponse::OnSuccess(const TaskResult& taskResult)
{
    Handleton::GetInstance<NBDProxy>()->RespondToWriteNBD(taskResult.GetUid(), 
                                                                        true);
    std::cout << "SUCCESS Write, uid = " << taskResult.GetUid().GetID() << 
                                                                    std::endl;
}

void ilrd::WriteResponse::OnFailure(const TaskResult& taskResult)
{
    Handleton::GetInstance<NBDProxy>()->RespondToWriteNBD(taskResult.GetUid(), 
                                                                        false);
    std::cout << "FAILURE Write, uid = " << taskResult.GetUid().GetID() << 
                                                                    std::endl;
}
/**
* @file: MinionWriteCommand.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of Minion_WriteCommnd.
* the only API function implementation is Execute(), which is responsible for
* executing the operation on the FileManager and call the function from
* MasterProxy (which sends a UDP message to MinionProxy).
*/

#include "Handleton.hpp"
#include "FileManager.hpp"
#include "MasterProxy.hpp"
#include "Minion_WriteCommand.hpp"
#include "Minion_WriteTaskArgs.hpp"

ilrd::ICommand::EXECUTE_PAIR ilrd::Minion_WriteCommand::Execute(ITaskArgs* args)
{
    Minion_WriteTaskArgs* writeArgs = static_cast<Minion_WriteTaskArgs*>(args);

    bool status = Handleton::GetInstance<FileManager>()->Write(
                                                        writeArgs->GetOffset(),
                                                        writeArgs->GetLength(),
                                                        writeArgs->GetBuffer());

    Handleton::GetInstance<MasterProxy>()->SendWriteMessageResponse(
                                                    writeArgs->GetUID(),status);
                                                        
    return { };
}
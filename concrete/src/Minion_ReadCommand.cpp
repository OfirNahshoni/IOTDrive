/**
* @file: MinionReadCommand.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of Minion_ReadCommnd.
* the only API function implementation is Execute(), which is responsible for
* executing the operation on the FileManager and call the function from
* MasterProxy (which sends a UDP message to MinionProxy).
*/

#include "Handleton.hpp"
#include "FileManager.hpp"
#include "MasterProxy.hpp"
#include "Minion_ReadCommand.hpp"
#include "Minion_ReadTaskArgs.hpp"

ilrd::ICommand::EXECUTE_PAIR ilrd::Minion_ReadCommand::Execute(ITaskArgs* args)
{
    Minion_ReadTaskArgs* readArgs = static_cast<Minion_ReadTaskArgs*>(args);

    bool status = Handleton::GetInstance<FileManager>()->Read(
                                                readArgs->GetOffset(),
                                                readArgs->GetLength(),
                                                readArgs->GetBuffer().get());

    Handleton::GetInstance<MasterProxy>()->SendReadMessageResponse(
                                                    readArgs->GetUID(), status,
                                                    readArgs->GetLength(),
                                                    readArgs->GetBuffer());

    return { };
}
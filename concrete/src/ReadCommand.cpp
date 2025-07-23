/**
* @file: ReadCommand.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of ReadCommand.
*/

#include "Handleton.hpp"
#include "ATaskArgs.hpp"
#include "ReadCommand.hpp"
#include "MinionManager.hpp"
#include "ResponseManager.hpp"

ilrd::ICommand::EXECUTE_PAIR ilrd::ReadCommand::Execute(ITaskArgs* args)
{
    ReadArgs* readArgs = static_cast<ReadArgs*>(args);

    Handleton::GetInstance<MinionManager>()->AddReadTask(readArgs->GetOffset(),
                                                        readArgs->GetLength(),
                                                        readArgs->GetUID(),
                                    static_cast<AMessage::MessageType>(AREAD));

    ResponseManager* responseManager = Handleton::GetInstance<ResponseManager>();
    EXECUTE_PAIR option;
    std::shared_ptr<size_t> counter(0);
    // size_t counter = 0;

    option.emplace([responseManager, uid = readArgs->GetUID(), counter]() {
        if (responseManager->IsTicketInMap(uid))
        {
            ++*counter;

            if (*counter == 100000)
            {
                responseManager->RemoveTicketFromMap(uid);
                return true;
            }
            
            return false;
        }
        
        return true;
    }, std::chrono::milliseconds(100));

    return option;
}
/**
* @file: WriteCommand.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of ReadCommand.
*/

#include "Handleton.hpp"
#include "ATaskArgs.hpp"
#include "WriteCommand.hpp"
#include "MinionManager.hpp"
#include "ResponseManager.hpp"

ilrd::ICommand::EXECUTE_PAIR ilrd::WriteCommand::Execute(ITaskArgs* args)
{
    WriteArgs* writeArgs = static_cast<WriteArgs*>(args);

    Handleton::GetInstance<MinionManager>()->AddWriteTask(writeArgs->GetOffset(),
                                                        writeArgs->GetLength(),
                                                        writeArgs->GetUID(),
                                    static_cast<AMessage::MessageType>(AWRITE),
                                    writeArgs->GetBuffer());
    
    
    ResponseManager* responseManager = Handleton::GetInstance<ResponseManager>();
    EXECUTE_PAIR option;
    std::shared_ptr<size_t> counter(0);
    // size_t counter = 0;
    
    option.emplace([responseManager, uid = writeArgs->GetUID(), counter]() {
        if (responseManager->IsTicketInMap(uid))
        {
            ++*counter;

            if (*counter == 1000000)
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
/**
* @file: ReadCommand.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the API of a Read Command. This
* Command is responsible to add ReadTask to the MinionManager.
*/

#ifndef ILRD_RD1645_READ_COMMAND_HPP
#define ILRD_RD1645_READ_COMMAND_HPP

#include "ICommand.hpp"         // ilrd::Command

namespace ilrd
{

class ReadCommand : public ICommand
{
public:
    EXECUTE_PAIR Execute(ITaskArgs* args);
};  // class ReadCommand

}   // namespace ilrd

#endif  // ILRD_RD1645_READ_COMMAND_HPP
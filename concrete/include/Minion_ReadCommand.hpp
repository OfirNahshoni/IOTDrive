/**
* @file: Minion_ReadCommand.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines an API of Read Command for Minion.
* it implements the interface ICommand.
*/

#ifndef MINION_READ_COMMAND_HPP
#define MINION_READ_COMMAND_HPP

#include "ICommand.hpp"

namespace ilrd
{

class Minion_ReadCommand : public ICommand
{
public:
    EXECUTE_PAIR Execute(ITaskArgs* args);
};  // class Minion_ReadCommand

}   // namespace ilrd

#endif  // MINION_READ_COMMAND_HPP
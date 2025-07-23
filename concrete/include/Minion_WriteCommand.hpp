/**
* @file: Minion_ReadCommand.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines an API of Read Command for Minion.
* it implements the interface ICommand.
*/

#ifndef MINION_WRITE_COMMAND_HPP
#define MINION_WRITE_COMMAND_HPP

#include "ICommand.hpp"

namespace ilrd
{

class Minion_WriteCommand : public ICommand
{
public:
    EXECUTE_PAIR Execute(ITaskArgs* args);
};  // class Minion_WriteCommand

}   // namespace ilrd

#endif  // MINION_WRITE_COMMAND_HPP
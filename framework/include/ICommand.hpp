/**
 * @file: ICommand.hpp
 * @author: Ofir Nahshoni
 * @brief: This is an interface of a Command that retunrs from the Framework.
 */

#ifndef ILRD_RD1645_ICOMMAND_HPP
#define ILRD_RD1645_ICOMMAND_HPP

#include <optional>             // std::optional
#include <functional>           // std::function
#include <chrono>               // std::chrono::milliseconds

#include "ITaskArgs.hpp"        // ITaskArgs

namespace ilrd
{

class ICommand
{
public:
    using EXECUTE_PAIR = std::optional<std::pair<std::function<bool()>, 
                                                    std::chrono::milliseconds>>;
    virtual EXECUTE_PAIR Execute(ITaskArgs* args) = 0;
};  // class ICommand

}   // namespace ilrd

#endif  // ILRD_RD1645_ICOMMAND_HPP
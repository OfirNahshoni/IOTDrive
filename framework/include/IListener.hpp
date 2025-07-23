/**
* @file: IListener.hpp
* @author: Ofir Nahshoni
* @brief: This is a file that defines an interface class IListener to make
* the most portable listen function (like select() in linux).
* @reviewer: Ofir1st
* @status: APPROVED
*/

#ifndef ILRD_RD1645_ILISTENER_HPP
#define ILRD_RD1645_ILISTENER_HPP

#include <vector>           // std::vector<T>

namespace ilrd
{

enum Mode
{
    READ = 0,
    WRITE = 1
};

class IListener
{
public:
    virtual std::vector<std::pair<int, Mode>> Listen(std::vector<std::pair<int, 
                                                                Mode>> fds) = 0;
};  // class IListener

}   // namespace ilrd

#endif  // ILRD_RD1645_ILISTENER_HPP
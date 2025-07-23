#include <iostream>

#include "Handleton.hpp"

extern "C" void PrintAddr()
{
    std::cout << "address = " << ilrd::Handleton::GetInstance<float>() << std::endl;
}
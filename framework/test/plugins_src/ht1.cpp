// framework/test/plugins_src/ht1.cpp

#include <iostream>

#include "Handleton.hpp"

extern "C" void PrintAddr()
{
    std::cout << "libht1.so Handleton<float> addr: "
              << ilrd::Handleton::GetInstance<float>() << std::endl;
}

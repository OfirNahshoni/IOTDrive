// framework/test/plugins_src/ht2.cpp

#include <iostream>

#include "Handleton.hpp"

extern "C" void PrintAddr()
{
    std::cout << "libht2.so Handleton<float> addr: "
              << ilrd::Handleton::GetInstance<float>() << std::endl;
}

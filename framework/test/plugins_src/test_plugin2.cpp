/**
* @file: test_plugin2.cpp
* @author: Ofir Nahshoni
* @brief: A source file to test dynamic linking of DirMonitor and DllLoader,
* that would be a shared object.
*/

#include <iostream>

__attribute__((constructor))
void Plugin2Ctor()
{
    std::cout << "[PLUGIN2] Ctor called" << std::endl;
}

__attribute__((destructor))
void Plugin2Dtor()
{
    std::cout << "[PLUGIN2] Dtor called" << std::endl;
}
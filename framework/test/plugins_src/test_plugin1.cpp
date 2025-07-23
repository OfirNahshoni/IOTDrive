/**
* @file: test_plugin1.cpp
* @author: Ofir Nahshoni
* @brief: A source file to test dynamic linking of DirMonitor and DllLoader,
* that would be a shared object.
*/

#include <iostream>

__attribute__((constructor))
void Plugin1Ctor()
{
    std::cout << "[PLUGIN1] Ctor called" << std::endl;
}

__attribute__((destructor))
void Plugin1Dtor()
{
    std::cout << "[PLUGIN1] Dtor called" << std::endl;
}

#include <string>       // std::string
#include <functional>   // std::function
#include <iostream>     // std::cout, std::endl
#include <dlfcn.h>      // dlopen, dlsym, dlclose

#include "test_macros.h"
#include "Handleton.hpp"

typedef void (*funcPtr)();

void TestsForHandleton();
void TestLoadDynamicLib();

int main()
{
    TestsForHandleton();
    TestLoadDynamicLib();
    PASS;
    
    return 0;
}

void TestsForHandleton()
{
    std::string* strHandle = ilrd::Handleton::GetInstance<std::string>();

    for (size_t i = 0; i < 4; ++i)
    {
        strHandle->append("hi");
    }

    std::cout << *strHandle << std::endl;
}

void TestLoadDynamicLib()
{
    float* fptr1 = ilrd::Handleton::GetInstance<float>();
    float* fptr2 = ilrd::Handleton::GetInstance<float>();

    TEST("same type check addresses", (fptr1 == fptr2), true);

    void* handler1 = dlopen("./libht1_shared_lib.so", RTLD_LAZY);

    if (!handler1)
    {
        std::cerr << "dlopen libht1.so failed: " << dlerror() << std::endl;
        return;
    }

    void* handler2 = dlopen("./libht2_shared_lib.so", RTLD_LAZY);
    if (!handler2)
    {
        std::cerr << "dlopen libht2.so failed: " << dlerror() << std::endl;
        dlclose(handler1);
        return;
    }


    funcPtr func1 = (funcPtr)dlsym(handler1, "PrintAddr");
    funcPtr func2 = (funcPtr)dlsym(handler2, "PrintAddr");

    func1();
    func2();

    dlclose(handler1);
    dlclose(handler2);
}
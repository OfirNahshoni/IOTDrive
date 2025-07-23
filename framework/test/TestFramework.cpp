/**
* @file: TestFramework.cpp
* @author: Ofir Nahshoni
* @brief: This is a test file for the framework of the final project. The 
* framework is listening to file descriptors, and handles requests when the
* FDs are detected by the system as active.
*/

#include <iostream>             // std::cin

#include "Reactor.hpp"          // ilrd::Reactor
#include "Framework.hpp"        // ilrd::Framework
#include "Handleton.hpp"        // ilrd::Handleton

namespace tests
{

enum Key
{
    READ = 0,
    WRITE = 1
};

class NBDReadArgs : public ilrd::ITaskArgs
{
public:
    NBDReadArgs(size_t offset, size_t length);
    // std::shared_ptr<char[]> GetMessage() const;
    int GetKey() const;

private:
    size_t m_offset;
    size_t m_length;
};  // class NBDReadArgs

NBDReadArgs::NBDReadArgs(size_t offset, size_t length) : 
                        m_offset(offset), 
                        m_length(length)
{ }

int NBDReadArgs::GetKey() const
{
    return READ;
}

class NBDProxy : public ilrd::IInputProxy
{
public:
    std::shared_ptr<ilrd::ITaskArgs> GetTaskArgs(int fd, ilrd::Mode mode);
};  // class NBDProxy

std::shared_ptr<ilrd::ITaskArgs> NBDProxy::GetTaskArgs(int fd, ilrd::Mode mode)
{
    size_t offset;
    size_t length;
    char input[BUFSIZ];
    
    std::cout << "Offset: ";
    std::sscanf(input, "%lu", &offset);

    std::cout << "Length: ";
    std::sscanf(input, "%lu", &length);
    
    return std::make_shared<NBDReadArgs>(offset, length);
}

class CommandRead : public ilrd::ICommand
{
public:
    explicit CommandRead() = default;
    ilrd::EXECUTE_PAIR Execute(ilrd::ITaskArgs* args);
};  // class CommandRead

ilrd::ICommand::EXECUTE_PAIR CommandRead::Execute(ilrd::ITaskArgs* args)
{
    NBDReadArgs* readArgs = dynamic_cast<NBDReadArgs*>(args);

    if (!readArgs)
    {
        std::runtime_error("failed to cast ItaskArgs to NBDReadArgs");
    }

    std::cout << "Read Command execution:" << std::endl;
    std::cout << "offset: " << std::endl;
    std::cout << "length: " << std::endl;

    return { [] { return true; }, std::chrono::milliseconds(1) };
}

std::shared_ptr<ilrd::ICommand> CreateReadCommand(ilrd::ITaskArgs* args)
{
    return std::make_shared<CommandRead>();
}

}   // namespace tests

void TestsForFramework();

int main()
{
    TestsForFramework();

    return 0;
}

void TestsForFramework()
{
    std::shared_ptr<ilrd::IInputProxy> proxy = std::make_shared<tests::NBDProxy>();
    ilrd::Framework::INPUTS_VECTOR inputsVector = { 
        {{STDIN_FILENO, ilrd::Mode::READ}, proxy}
    };
    ilrd::Framework::FACTORY_VEC_TYPE factoryVector = {
        {tests::READ, tests::CreateReadCommand}
    };
    ilrd::Framework fw(inputsVector, factoryVector);

    fw.Run();
}
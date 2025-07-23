

#include <iostream>

#include "Factory.hpp"      // ilrd::Factory
#include "ICommand.hpp"     // ilrd::ICommand

#include "Handleton.hpp"    // ilrd::Handleton

class SpecialReadCommand : public ilrd::ICommand
{
public:
    explicit SpecialReadCommand() = default;
    ilrd::EXECUTE_PAIR Execute(ilrd::ITaskArgs* args);
};  // class SpecialReadCommand

ilrd::EXECUTE_PAIR SpecialReadCommand::Execute(ilrd::ITaskArgs* args)
{
    // SpecialReadArgs* sreadArgs = std::static_pointer_cast<*>(args);
    // std::cout << "Msg: " << sreadArgs->GetMsg() << " , ";
    // std::cout << "Size: " << sreadArgs->GetSizeMsg() << std::endl;
    std::cout << "SpecialReadCommand::Execute" << std::endl;

    return { [] { return true; }, std::chrono::milliseconds(1) };
}

// factory registration function
extern "C" void CreateSpecialReadCommand()
{
    std::cout << "[PLUGIN] Registering Special Read command" << std::endl;

    ilrd::Handleton::GetInstance<ilrd::Factory<int, ilrd::ICommand>>()->
        Register(0, []() {
            return std::make_shared<SpecialReadCommand>();
        });
}

__attribute__((constructor))
void ReadPluginsCtor()
{
    std::cout << "Special Read plugin was added" << std::endl;
    CreateSpecialReadCommand();
}

__attribute__((destructor))
void ReadPluginsDtor()
{
    std::cout << "Special Read plugin was deleted" << std::endl;
}
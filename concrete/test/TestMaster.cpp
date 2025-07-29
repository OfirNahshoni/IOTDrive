/**
* @file: TestMaster.cpp
* @author: Ofir Nahshoni
* @brief: This is the main file of the master. The master is the concrete
* component that has all the main components, like:
* Framework, MinionManager, ResponseManager.
*/

#include "Factory.hpp"              // ilrd::Factory
#include "NBDProxy.hpp"             // ilrd::NBDProxy
#include "Framework.hpp"            // ilrd::Framework
#include "NBDServer.hpp"            // ilrd::NBDServer
#include "ITaskArgs.hpp"            // ilrd::ITaskArgs
#include "MinionProxy.hpp"          // ilrd::MinionProxy
#include "ReadCommand.hpp"          // ilrd::ReadCommand
#include "WriteCommand.hpp"         // ilrd::WriteCommand
#include "MinionManager.hpp"        // ilrd::MinionManager
#include "ResponseManager.hpp"      // ilrd::ResponseManager

using namespace ilrd;

void TestsStdin(char* deviceName);

int main(int argc, char* argv[])
{
    (void)argc;

    TestsStdin(argv[1]);

    return 0;
}

std::shared_ptr<ICommand> CreateReadCommand(ITaskArgs* args)
{
    (void)args;

    return std::make_shared<ReadCommand>();
}

std::shared_ptr<ICommand> CreateWriteCommand(ITaskArgs* args)
{
    (void)args;

    return std::make_shared<WriteCommand>();
}

std::shared_ptr<ilrd::AMessage> CreateReadResponse()
{
    return std::make_shared<ilrd::ReadResponseMessage>();
}

std::shared_ptr<ilrd::AMessage> CreateWriteResponse()
{
    return std::make_shared<ilrd::WriteResponseMessage>();
}

std::shared_ptr<ilrd::AMessage> CreateReadSend()
{
    return std::make_shared<ilrd::ReadSendMessage>();
}

std::shared_ptr<ilrd::AMessage> CreateWriteSend()
{
    return std::make_shared<ilrd::WriteSendMessage>();
}

void TestsStdin(char* deviceName)
{
    const size_t blockSize = 4 * 1024 * 1024;

    // MinionProxy
    std::shared_ptr<IMinionProxy> m1 = std::make_shared<MinionProxy>(
                        "5000","5001", "10.1.0.228");
    std::shared_ptr<IMinionProxy> m2 = std::make_shared<MinionProxy>(
                        "5003","5002", "10.1.0.130");
    std::vector<std::shared_ptr<IMinionProxy>> minions = {m1, m2};

    // MinionManager
    Handleton::GetInstance<MinionManager>()->Init(blockSize, minions);

    // NBDProxy & NBDServer
    ilrd::NBDServer nbdServer(deviceName, 2 * blockSize);
    Handleton::GetInstance<Factory<Mode, ATaskArgs, NBDArgs>>();
    NBDProxy* nbdProxy = Handleton::GetInstance<NBDProxy>();
    Handleton::GetInstance<NBDProxy>()->Init(nbdServer);

    // ResponseManager
    Handleton::GetInstance<ResponseManager>()->Init(*nbdProxy);
    
    // register socket of NBDServer to the Reactor of the Framework
    Framework::INPUTS_VECTOR inputsVector = {
        {{nbdProxy->GetSocketFD(), Mode::READ}, 
                                        std::shared_ptr<IInputProxy>(nbdProxy)}
    };
    Framework::FACTORY_VEC_TYPE factoryVector = {
        std::make_pair(static_cast<int>(Mode::READ), CreateReadCommand),
        std::make_pair(static_cast<int>(Mode::WRITE), CreateWriteCommand)
    };

    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
        Register(ilrd::AMessage::ClassType::READ_RESPONSE, CreateReadResponse);
    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
                Register(ilrd::AMessage::ClassType::READ_SEND, CreateReadSend);
    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
    Register(ilrd::AMessage::ClassType::WRITE_RESPONSE, CreateWriteResponse);
    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
            Register(ilrd::AMessage::ClassType::WRITE_SEND, CreateWriteSend);
    
    // Framework
    Framework fw(inputsVector, factoryVector);
    fw.Run();
}
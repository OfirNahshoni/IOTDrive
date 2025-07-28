/**
* @file: TestDemoMionion2.cpp
* @author: Ofir Nahshoni
* @brief: This is a file that simulate the communication between the
* MinionProxy and the Minion itself (which will a Raspberry PI). this is, for
* now, a local process in the same computer as the master is.
*/

#include <iostream>

#include "Factory.hpp"
#include "AMessage.hpp"
#include "Framework.hpp"
#include "ITaskArgs.hpp"
#include "Handleton.hpp"
#include "FileManager.hpp"
#include "MasterProxy.hpp"
#include "Minion_ReadCommand.hpp"
#include "Minion_WriteCommand.hpp"

std::shared_ptr<ilrd::ICommand> CreateReadCmd(ilrd::ITaskArgs* args);
std::shared_ptr<ilrd::ICommand> CreateWriteCmd(ilrd::ITaskArgs* args);

void TestForReadCommandFromMaster();

int main()
{
    TestForReadCommandFromMaster();

    return 0;
}

std::shared_ptr<ilrd::ICommand> CreateReadCmd(ilrd::ITaskArgs* args)
{
    (void)args;
    return std::make_shared<ilrd::Minion_ReadCommand>();
}

std::shared_ptr<ilrd::ICommand> CreateWriteCmd(ilrd::ITaskArgs* args)
{
    (void)args;
    return std::make_shared<ilrd::Minion_WriteCommand>();
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

void TestForReadCommandFromMaster()
{
    // MasterProxy
    ilrd::MasterProxy* masterProxy =
                            ilrd::Handleton::GetInstance<ilrd::MasterProxy>();

    // set self port
    masterProxy->Init("5002");

    ilrd::Handleton::GetInstance<ilrd::FileManager>()->Init("./minionB.bin");

    // register the UDP's fd of MasterProxy to the Reactor of the Framework
    ilrd::Framework::INPUTS_VECTOR reactorVector = {
        {{masterProxy->GetSocketFD(), ilrd::Mode::READ},
                                std::shared_ptr<ilrd::IInputProxy>(masterProxy)}
    };
    ilrd::Framework::FACTORY_VEC_TYPE cmdFactory = {
        std::make_pair(static_cast<int>(ilrd::Mode::READ), CreateReadCmd),
        std::make_pair(static_cast<int>(ilrd::Mode::WRITE), CreateWriteCmd)
    };

    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
        Register(ilrd::AMessage::ClassType::READ_RESPONSE, CreateReadResponse);
    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
                Register(ilrd::AMessage::ClassType::READ_SEND, CreateReadSend);
    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
    Register(ilrd::AMessage::ClassType::WRITE_RESPONSE, CreateWriteResponse);
    ilrd::Handleton::GetInstance<ilrd::Factory<uint32_t, ilrd::AMessage>>()->
            Register(ilrd::AMessage::ClassType::WRITE_SEND, CreateWriteSend);

    ilrd::Framework fw(reactorVector, cmdFactory);
    fw.Run();
}
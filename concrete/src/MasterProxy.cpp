/**
* @file: MasterProxy.hpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API for MasterProxy. this
* API is responsible for sending the responses to MinionProxy, which is on the
* Master's side. only the Command APIs call SendReadMessageResponse or
* SendWriteMessageResponse to MinionProxy, using UDP Socket.
*/

#include <cstring>                  // memcpy
#include <memory>                   // std::static_pointer_cast

#include <iostream>                 // std::cout for debug

#include "AMessage.hpp"
#include "MasterProxy.hpp"
#include "Minion_ReadTaskArgs.hpp"
#include "Minion_WriteTaskArgs.hpp"

void ilrd::MasterProxy::Init(const std::string& port)
{
    m_udpSocket.emplace(port, true);
}

int ilrd::MasterProxy::GetSocketFD() const
{
    return m_udpSocket.value().GetFD();
}

void ilrd::MasterProxy::SendReadMessageResponse(const UID& uid, bool status, 
                                    size_t length, std::shared_ptr<char[]> data)
{
    ReadResponseMessage msg(uid, status, data.get(), length);

    std::cout << "msg size: " << msg.GetSize() << std::endl;

    char* buffer = new char[msg.GetSize()];
    msg.ToBuffer(buffer);
    
    std::unique_lock lock(m_mutex);
    size_t sendReturn = m_udpSocket.value().Send(buffer, msg.GetSize());
    lock.unlock();

    std::cout << "RETURN SEND: " << sendReturn << std::endl;
    
    std::cout << "Read Command sent to the Master:" << std::endl;
    std::cout << "uid = " << uid.GetID() << std::endl;
    std::cout << "status: " << status << std::endl;
    std::cout << "length: " << length << std::endl;
    std::cout << "buffer: " << data.get() << std::endl;
    
    delete[] buffer;
}

void ilrd::MasterProxy::SendWriteMessageResponse(const UID& uid, bool status)
{
    WriteResponseMessage msg(uid, status);
    char* buffer = new char[msg.GetSize()];
    msg.ToBuffer(buffer);

    std::unique_lock lock(m_mutex);
    m_udpSocket.value().Send(buffer, msg.GetSize());
    lock.unlock();

    std::cout << "Write Command sent to the Master:" << std::endl;
    std::cout << "uid = " << uid.GetID() << std::endl;
    std::cout << "status: " << status << std::endl;

    delete[] buffer;
}

std::shared_ptr<ilrd::ITaskArgs> ilrd::MasterProxy::GetTaskArgs(int fd, 
                                                                    Mode mode)
{
    static_cast<void>(fd);
    static_cast<void>(mode);

    char buffer[BUFSIZ];

    {
        std::unique_lock lock(m_mutex);
        m_udpSocket.value().Receive(buffer, BUFSIZ);
    }

    std::shared_ptr<char[]> data = nullptr;
    std::shared_ptr<AMessage> msg = nullptr;
    std::shared_ptr<ITaskArgs> args = nullptr;
    char* runner = buffer;

    uint32_t size = *reinterpret_cast<uint32_t*>(runner);
    runner += sizeof(size);
    uint32_t type = *reinterpret_cast<uint32_t*>(runner); 
    runner += sizeof(type);

    if (type == AMessage::ClassType::READ_SEND)
    {
        msg = std::make_shared<ReadSendMessage>();
        msg->FromBuffer(runner);
        data = std::make_shared<char[]>(msg->GetLength());

        args = std::make_shared<Minion_ReadTaskArgs>(msg->GetUID(), 
                                                    msg->GetOffset(),
                                                    msg->GetLength(),
                                                    data);
        
        std::cout << "[MasterProxy] got ReadSend message:" << std::endl;
        std::cout << "(and entered to the Framework):" << std::endl;
        std::cout << "uid: " << msg->GetUID().GetID() << std::endl;
        std::cout << "Offset: " << msg->GetOffset() << std::endl;
        std::cout << "Length: " << msg->GetLength() << std::endl;
    }
    else if (type == AMessage::ClassType::WRITE_SEND)
    {
        msg = std::make_shared<WriteSendMessage>();
        msg->FromBuffer(runner);
        data = std::make_shared<char[]>(msg->GetLength());

        memcpy(data.get(), std::static_pointer_cast<WriteSendMessage>(
                                        msg)->GetBuffer(), msg->GetLength());

        args = std::make_shared<Minion_WriteTaskArgs>(msg->GetUID(), 
                                                        msg->GetOffset(),
                                                        msg->GetLength(),
                                                        data);
        
        std::cout << "[MasterProxy] got WriteSend message:" << std::endl;
        std::cout << "(and entered to the Framework):" << std::endl;
        std::cout << "uid: " << msg->GetUID().GetID() << std::endl;
        std::cout << "Offset: " << msg->GetOffset() << std::endl;
        std::cout << "Length: " << msg->GetLength() << std::endl;
        std::cout << "buffer: " << data.get() << std::endl;
    }
    else
    {
        throw std::runtime_error("invalid message type");
    }

    return args;
}
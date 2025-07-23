/**
* @file: MinionProxy.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API MinionProxy, which is
* a concrete API that responsible to send (with UDP sockets) the tasks it
* received.
*/

#include <iostream>

#include "Factory.hpp"
#include "Handleton.hpp"
#include "MinionProxy.hpp"

ilrd::MinionProxy::MinionProxy(const std::string& portSelf, 
                                const std::string& portTarget, 
                                const std::string& ipTarget) : 
                                m_udp(portSelf)
{
    m_udp.SetTargetAddr(portTarget, ipTarget);
}

void ilrd::MinionProxy::AddWriteTask(size_t offset, size_t length, 
                const UID& uid, std::shared_ptr<char[]> data,
                std::function<void(const std::shared_ptr<AMessage>&)> onDone)
{
    WriteSendMessage writeMsg(uid, offset, length, data.get());
    char* buffer = new char[writeMsg.GetSize()];
    writeMsg.ToBuffer(buffer);

    {
        std::unique_lock lock(m_mutex);
        m_map[writeMsg.GetUID()] = onDone;
        m_udp.Send(buffer, writeMsg.GetSize());
    }

    std::cout << "[MinionProxy] SendWrite uid: " << 
                                        writeMsg.GetUID().GetID() << std::endl;

    delete[] buffer;
}

void ilrd::MinionProxy::AddReadTask(size_t offset, size_t length, 
                const UID& uid,
                std::function<void(const std::shared_ptr<AMessage>&)> onDone)
{
    ReadSendMessage readMsg(uid, offset, length);
    
    char* buffer = new char[readMsg.GetSize()];
    readMsg.ToBuffer(buffer);
    std::cout << "[MinionProxy] SendRead uid: " << 
    readMsg.GetUID().GetID() << std::endl;
    std::cout << "\tOffset: " << readMsg.GetOffset() << std::endl;
    std::cout << "\tLength: " << readMsg.GetLength() << std::endl;
    
    {
        std::unique_lock lock(m_mutex);
        m_map[readMsg.GetUID()] = onDone;
        m_udp.Send(buffer, readMsg.GetSize());
    }

    delete[] buffer;
}

int ilrd::MinionProxy::GetMinionFD()
{
    return m_udp.GetFD();
}

void ilrd::MinionProxy::OnMinionFDWakeup()
{
    // [size (4B), type (4B), uid, object]
    std::cout << "minion woke up" << std::endl;
    
    char buffer[BUFSIZ];
    char* inData = NULL;
    
    {
        std::unique_lock lock(m_mutex);
        m_udp.Receive(buffer, BUFSIZ);
    }
    
    inData = buffer;
    uint32_t size = *(reinterpret_cast<uint32_t*>(inData));
    inData += sizeof(size);
    uint32_t type = *(reinterpret_cast<uint32_t*>(inData));
    inData += sizeof(type);

    std::shared_ptr<AMessage> msg = Handleton::GetInstance<Factory<uint32_t, 
                                            ilrd::AMessage>>()->Create(type);
    
    msg->FromBuffer(inData);
    std::cout << "[MinionProxy] response uid = " << msg->GetUID().GetID() << 
                                                                    std::endl;

    std::function<void(const std::shared_ptr<AMessage>&)> on_done;

    {
        std::unique_lock lock(m_mutex);
        on_done = m_map.at(msg->GetUID());
        m_map.erase(msg->GetUID());
    }

    on_done(msg);
}
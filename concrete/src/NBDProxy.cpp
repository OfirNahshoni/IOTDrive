/**
* @file: NBDProxy.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of NBDProxy, that is
* responsible to create IRequest and register this to ResponseManager.
*/

#include <cstring>
#include <iostream>
#include <linux/nbd.h>

#include "Factory.hpp"
#include "NBDProxy.hpp"
#include "Handleton.hpp"

void ilrd::NBDProxy::Init(NBDServer& nbd)
{
    m_tcpSocket.emplace(nbd.GetTCPSocket());
}

ilrd::NBDProxy::NBDProxy() : m_tcpSocket()
{
    Factory<Mode, ATaskArgs, NBDArgs>* factory = 
                    Handleton::GetInstance<Factory<Mode, ATaskArgs, NBDArgs>>();

    factory->Register(Mode::READ, [](const NBDArgs& args) {
        return std::make_shared<ReadArgs>(args);
    });

    factory->Register(Mode::WRITE, [](const NBDArgs& args) {
        return std::make_shared<WriteArgs>(args);
    });
}

int ilrd::NBDProxy::GetSocketFD() const
{
    return m_tcpSocket.value().GetFD();
}

std::shared_ptr<ilrd::ITaskArgs> ilrd::NBDProxy::GetTaskArgs(int fd, Mode mode)
{
    (void)fd;
    (void)mode;

    nbd_request request = {};
    std::unique_lock lock(m_mutex);

    {
        // std::unique_lock lock(m_mutex);
        m_tcpSocket.value().Receive(reinterpret_cast<char*>(&request), 
                                                        sizeof(nbd_request));
    }

    NBDArgs args = {NBDServer::Ntohll(request.from), ntohl(request.len), nullptr};
    std::shared_ptr<ATaskArgs> taskArgs;
    
    if (ntohl(request.type) == NBD_CMD_READ)
    {
        taskArgs = Handleton::GetInstance<Factory<Mode, ATaskArgs, 
                                        NBDArgs>>()->Create(Mode::READ, args);
    }
    else if (ntohl(request.type) == NBD_CMD_WRITE)
    {
        // get the buffer to write
        // std::unique_lock lock(m_mutex);
        std::shared_ptr<char[]> buffer(new char[ntohl(request.len)]);
        m_tcpSocket.value().Receive(buffer.get(), ntohl(request.len));
        args.m_buffer = buffer;
        taskArgs = Handleton::GetInstance<Factory<Mode, ATaskArgs, 
                                        NBDArgs>>()->Create(Mode::WRITE, args);
    }

    {
        // std::unique_lock lock(m_mutex);
        std::memcpy(m_map[taskArgs->GetUID()].data(), request.handle, 
                                                        sizeof(request.handle));
    }

    m_dispatcherNewTaskArgs.Notify(taskArgs);
    
    return taskArgs;
}

void ilrd::NBDProxy::RespondToReadNBD(const UID& uid, bool status, 
                                                size_t length, 
                                                std::shared_ptr<char[]> buffer)
{
    nbd_reply reply;
    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(!status);

    std::unique_lock lock(m_mutex);
    std::memcpy(reply.handle, m_map[uid].data(), sizeof(reply.handle));
    m_tcpSocket.value().Send(reinterpret_cast<const char*>(&reply), sizeof(reply));
    m_tcpSocket.value().Send(buffer.get(), length);
    m_map.erase(uid);
}

void ilrd::NBDProxy::RespondToWriteNBD(const UID& uid, bool status)
{
    nbd_reply reply;
    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(!status);

    std::unique_lock lock(m_mutex);
    std::memcpy(reply.handle, m_map[uid].data(), sizeof(reply.handle));
    m_tcpSocket.value().Send(reinterpret_cast<const char*>(&reply), sizeof(reply));
    m_map.erase(uid);
}

void ilrd::NBDProxy::RegisterForNewTaskArgs(ACallback<std::shared_ptr<
                                                        ATaskArgs>>* callback)
{
    m_dispatcherNewTaskArgs.Register(callback);
}

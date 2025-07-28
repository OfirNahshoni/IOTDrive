/**
* @file: AMessage.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API of abstract Message.
* It's decoupled from a Message that received from the MinionProxy, and a
* Message that is sent to MinionProxy.
*/

#include <cstring>

#include "AMessage.hpp"

/*-----------------------------------AMessage---------------------------------*/
ilrd::AMessage::AMessage(const UID& uid) : m_uid(uid)
{ }

const ilrd::UID& ilrd::AMessage::GetUID() const
{
    return m_uid;
}

uint32_t ilrd::AMessage::GetSize() const
{
    return (sizeof(UID) + 2 * sizeof(uint32_t));
}

uint32_t ilrd::AMessage::GetOffset() const
{
    return 0;
}

uint32_t ilrd::AMessage::GetLength() const
{
    return 0;
}

char* ilrd::AMessage::ToBuffer(char* buffer)
{
    *(reinterpret_cast<uint32_t*>(buffer)) = GetSize();
    buffer += sizeof(uint32_t);

    *(reinterpret_cast<uint32_t*>(buffer)) = GetClassType();
    buffer += sizeof(uint32_t);

    *(reinterpret_cast<UID*>(buffer)) = m_uid;
    buffer += sizeof(UID);

    return buffer;
}

char* ilrd::AMessage::FromBuffer(char* buffer)
{
    m_uid = *(reinterpret_cast<UID*>(buffer));
    buffer += sizeof(UID);
    
    return buffer;
}

/*-------------------------------ReadSendMessage------------------------------*/
ilrd::ReadSendMessage::ReadSendMessage() : AMessage(UID()), m_offset(0), 
                                                                    m_length(0)
{ }

ilrd::ReadSendMessage::ReadSendMessage(const UID& uid, uint32_t offset, 
                                        uint32_t length) : AMessage(uid), 
                                                            m_offset(offset), 
                                                            m_length(length)
{ }

ilrd::AMessage::MessageType ilrd::ReadSendMessage::GetMessageType() const
{
    return MSG_READ;
}

uint32_t ilrd::ReadSendMessage::GetSize() const
{
    return (AMessage::GetSize() + 2 * sizeof(uint32_t));
}

ilrd::AMessage::ClassType ilrd::ReadSendMessage::GetClassType() const
{
    return READ_SEND;
}

char* ilrd::ReadSendMessage::ToBuffer(char* buffer)
{
    buffer = AMessage::ToBuffer(buffer);

    *(reinterpret_cast<uint32_t*>(buffer)) = m_offset;
    buffer += sizeof(uint32_t);

    *(reinterpret_cast<uint32_t*>(buffer)) = m_length;
    buffer += sizeof(uint32_t);
    
    return buffer;
}

char* ilrd::ReadSendMessage::FromBuffer(char* buffer)
{
    buffer = AMessage::FromBuffer(buffer);

    m_offset = *(reinterpret_cast<uint32_t*>(buffer));
    buffer += sizeof(uint32_t);

    m_length = *(reinterpret_cast<uint32_t*>(buffer));
    buffer += sizeof(uint32_t);

    return buffer;
}

uint32_t ilrd::ReadSendMessage::GetOffset() const
{
    return m_offset;
}

uint32_t ilrd::ReadSendMessage::GetLength() const
{
    return m_length;
}

/*-----------------------------ReadResponseMessage----------------------------*/
ilrd::ReadResponseMessage::ReadResponseMessage() : AMessage(UID()), 
                                m_status(false), m_length(0), m_buffer(nullptr)
{ }

ilrd::ReadResponseMessage::ReadResponseMessage(const UID& uid, bool status, 
                                            char* buffer, uint32_t length) : 
                                            AMessage(uid), 
                                            m_status(status), 
                                            m_length(length), 
                                            m_buffer(new char[m_length])
{
    memcpy(m_buffer, buffer, m_length);
}

ilrd::ReadResponseMessage::~ReadResponseMessage()
{
    delete[] m_buffer;
}

ilrd::AMessage::MessageType ilrd::ReadResponseMessage::GetMessageType() const
{
    return MSG_READ;
}

uint32_t ilrd::ReadResponseMessage::GetSize() const
{
    return (AMessage::GetSize() + sizeof(bool) + m_length + sizeof(m_length));
}

ilrd::AMessage::ClassType ilrd::ReadResponseMessage::GetClassType() const
{
    return READ_RESPONSE;
}

char* ilrd::ReadResponseMessage::ToBuffer(char* buffer)
{
    buffer = AMessage::ToBuffer(buffer);

    *(reinterpret_cast<bool*>(buffer)) = m_status;
    buffer += sizeof(bool);
    *(reinterpret_cast<uint32_t*>(buffer)) = m_length;
    buffer += sizeof(uint32_t);

    memcpy(buffer, m_buffer, m_length);
    buffer += m_length;
    
    return buffer;
}

char* ilrd::ReadResponseMessage::FromBuffer(char* buffer)
{
    buffer = AMessage::FromBuffer(buffer);

    m_status = *(reinterpret_cast<bool*>(buffer));
    buffer += sizeof(bool);
    m_length = *(reinterpret_cast<uint32_t*>(buffer));
    buffer += sizeof(uint32_t);

    delete[] m_buffer;
    m_buffer = new char[m_length];
    memcpy(m_buffer, buffer, m_length);
    buffer += m_length;
    
    return buffer;
}

bool ilrd::ReadResponseMessage::GetStatus() const
{
    return m_status;
}

uint32_t ilrd::ReadResponseMessage::GetLength() const
{
    return m_length;
}

char* ilrd::ReadResponseMessage::GetBuffer() const
{
    return m_buffer;
}

/*------------------------------WriteSendMessage------------------------------*/
ilrd::WriteSendMessage::WriteSendMessage() : AMessage(UID()), m_offset(0),
                                            m_length(0), m_buffer(new char[1])
{ }

ilrd::WriteSendMessage::WriteSendMessage(const UID& uid, uint32_t offset, 
                                        uint32_t length, char* buffer) :
                                        AMessage(uid), 
                                        m_offset(offset),
                                        m_length(length),
                                        m_buffer(new char[m_length])
{
    memcpy(m_buffer, buffer, m_length);
}

ilrd::WriteSendMessage::~WriteSendMessage()
{
    delete[] m_buffer;
}

ilrd::AMessage::MessageType ilrd::WriteSendMessage::GetMessageType() const
{
    return MSG_WRITE;
}

uint32_t ilrd::WriteSendMessage::GetSize() const
{
    return (AMessage::GetSize() + 2 * sizeof(uint32_t) + m_length);
}

ilrd::AMessage::ClassType ilrd::WriteSendMessage::GetClassType() const
{
    return WRITE_SEND;
}

char* ilrd::WriteSendMessage::ToBuffer(char* buffer)
{
    buffer = AMessage::ToBuffer(buffer);

    *(reinterpret_cast<uint32_t*>(buffer)) = m_offset;
    buffer += sizeof(uint32_t);
    *(reinterpret_cast<uint32_t*>(buffer)) = m_length;
    buffer += sizeof(uint32_t);

    memcpy(buffer, m_buffer, m_length);
    buffer += m_length;
    
    return buffer;
}

char* ilrd::WriteSendMessage::FromBuffer(char* buffer)
{
    buffer = AMessage::FromBuffer(buffer);

    m_offset = *(reinterpret_cast<uint32_t*>(buffer));
    buffer += sizeof(uint32_t);
    m_length = *(reinterpret_cast<uint32_t*>(buffer));
    buffer += sizeof(uint32_t);

    delete[] m_buffer;

    m_buffer = new char[m_length];
    memcpy(m_buffer, buffer, m_length);
    buffer += m_length;
    
    return buffer;
}

uint32_t ilrd::WriteSendMessage::GetOffset() const
{
    return m_offset;
}

uint32_t ilrd::WriteSendMessage::GetLength() const
{
    return m_length;
}

char* ilrd::WriteSendMessage::GetBuffer() const
{
    return m_buffer;
}

/*----------------------------WriteResponseMessage----------------------------*/
ilrd::WriteResponseMessage::WriteResponseMessage() : AMessage(UID()), 
                                                                m_status(false)
{ }

ilrd::WriteResponseMessage::WriteResponseMessage(const UID& uid, bool status) : 
                                                AMessage(uid), m_status(status)
{ }

ilrd::AMessage::MessageType ilrd::WriteResponseMessage::GetMessageType() const
{
    return MSG_WRITE;
}

uint32_t ilrd::WriteResponseMessage::GetSize() const
{
    return (AMessage::GetSize() + sizeof(bool));
}

ilrd::AMessage::ClassType ilrd::WriteResponseMessage::GetClassType() const
{
    return WRITE_RESPONSE;
}

char* ilrd::WriteResponseMessage::ToBuffer(char* buffer)
{
    buffer = AMessage::ToBuffer(buffer);

    *(reinterpret_cast<bool*>(buffer)) = m_status;
    buffer += sizeof(bool);
    
    return buffer;
}

char* ilrd::WriteResponseMessage::FromBuffer(char* buffer)
{
    buffer = AMessage::FromBuffer(buffer);

    m_status = *(reinterpret_cast<bool*>(buffer));
    buffer += sizeof(bool);
    
    return buffer;
}

bool ilrd::WriteResponseMessage::GetStatus() const
{
    return m_status;
}
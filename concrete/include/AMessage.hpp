/**
* @file: AMessage.hpp
* @author: Ofir Nahshoni
* @brief: This is a header file that defines the API for abstract Message
* object that conaints the important details of a Command to send to Minion.
* This header also defines more derived objects of AMessage:
* 1) ReadSendMessage
* 2) ReadResponseMessage
* 3) WriteSendMessage
* 4) WriteResponseMessage
*/

#ifndef ILRD_RD1645_AMESSAGE_HPP
#define ILRD_RD1645_AMESSAGE_HPP

#include <memory>           // std::shared_ptr

#include "UID.hpp"          // ilrd::UID

namespace ilrd
{

class AMessage
{
public:
    enum MessageType
    {
        MSG_READ = 0,
        MSG_WRITE = 1
    };

    enum ClassType : uint32_t
    {
        READ_SEND = 0,
        READ_RESPONSE = 1,
        WRITE_SEND = 2,
        WRITE_RESPONSE = 3
    };

    AMessage(const UID& uid);
    ~AMessage() = default;
    
    virtual uint32_t GetSize() const;
    virtual uint32_t GetOffset() const;
    virtual uint32_t GetLength() const;
    virtual MessageType GetMessageType() const = 0;
    virtual ClassType GetClassType() const = 0;
    virtual char* ToBuffer(char* buffer) = 0;
    virtual char* FromBuffer(char* buffer) = 0;

    const UID& GetUID() const;

private:
    UID m_uid;
};  // class AMessage

// TODO: add AResponseMessage and ASendMessage

class ReadSendMessage : public AMessage
{
public:
    ReadSendMessage();
    explicit ReadSendMessage(const UID& uid, uint32_t offset, uint32_t length);
    MessageType GetMessageType() const;
    uint32_t GetSize() const;
    AMessage::ClassType GetClassType() const;
    char* ToBuffer(char* buffer);
    char* FromBuffer(char* buffer);

    // for debug
    uint32_t GetOffset() const;
    uint32_t GetLength() const;

private:
    uint32_t m_offset;
    uint32_t m_length;
};  // class ReadSendMessage

class ReadResponseMessage : public AMessage
{
public:
    ReadResponseMessage();
    explicit ReadResponseMessage(const UID& uid, bool status, char* buffer, 
                                                            uint32_t length);
    ~ReadResponseMessage();
    MessageType GetMessageType() const;
    uint32_t GetSize() const;
    AMessage::ClassType GetClassType() const;
    char* ToBuffer(char* buffer);
    char* FromBuffer(char* buffer);

    // for debug
    bool GetStatus() const;
    uint32_t GetLength() const;
    char* GetBuffer() const;

private:
    bool m_status;
    uint32_t m_length;
    char* m_buffer;
};  // class ReadResponseMessage

class WriteSendMessage : public AMessage
{
public:
    WriteSendMessage();
    explicit WriteSendMessage(const UID& uid, uint32_t offset, uint32_t length, 
                                                                char* buffer);
    ~WriteSendMessage();
    MessageType GetMessageType() const;
    uint32_t GetSize() const;
    AMessage::ClassType GetClassType() const;
    char* ToBuffer(char* buffer);
    char* FromBuffer(char* buffer);

    // for debug
    uint32_t GetOffset() const;
    uint32_t GetLength() const;
    char* GetBuffer() const;

private:
    uint32_t m_offset;
    uint32_t m_length;
    char* m_buffer;
};  // class WriteSendMessage

class WriteResponseMessage : public AMessage
{
public:
    WriteResponseMessage();
    explicit WriteResponseMessage(const UID& uid, bool status);
    MessageType GetMessageType() const;
    uint32_t GetSize() const;
    AMessage::ClassType GetClassType() const;
    char* ToBuffer(char* buffer);
    char* FromBuffer(char* buffer);

    // for debug
    bool GetStatus() const;

private:
    bool m_status;
};  // class WriteResponseMessage

}   // namespace ilrd

#endif  // ILRD_RD1645_AMESSAGE_HPP
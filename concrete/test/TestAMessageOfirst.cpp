// concrete/test/TestAMessage.cpp

#include <iostream>

#include "AMessage.hpp"
#include "test_macros.h"

void TestReadMessageSend()
{
	std::cout << "TestReadMessageSend" << std::endl;
	ilrd::ReadSendMessage readMessageSend(ilrd::UID(), 4, 6);
	auto sendBuff = new char[readMessageSend.GetSize()]{};
	readMessageSend.ToBuffer(sendBuff);
	ilrd::ReadSendMessage readMessageRecieved;
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	readMessageRecieved.FromBuffer(runner);
	std::cout << readMessageRecieved.GetOffset() << " , " << 
                readMessageRecieved.GetLength() << std::endl;
	delete[] sendBuff;
}

void TestWriteMessageSend()
{
	std::cout << "TestWriteMessageSend" << std::endl;
	const auto data = std::shared_ptr<char[]>(new char[8]{"bla bla"});
	ilrd::WriteSendMessage writeMessageSend(ilrd::UID(), 4, 8, data.get());
	const auto sendBuff = new char[writeMessageSend.GetSize()];
	writeMessageSend.ToBuffer(sendBuff);
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	ilrd::WriteSendMessage writeMessageRecieved;
	writeMessageRecieved.FromBuffer(runner);
	std::cout << writeMessageRecieved.GetOffset() << " , " << 
                                writeMessageRecieved.GetLength() << std::endl;
	std::cout << "buffer: " << writeMessageRecieved.GetBuffer() << std::endl;
	delete[] sendBuff;
}

void TestWriteMessageResponse()
{
	std::cout << "TestWriteMessageResponse" << std::endl;
	auto data = std::shared_ptr<const char[]>(new const char[8]{"bla bla"});
	ilrd::WriteResponseMessage writeMessageResp(ilrd::UID(), true);
	const auto sendBuff = new char[writeMessageResp.GetSize()];
	writeMessageResp.ToBuffer(sendBuff);
	ilrd::WriteResponseMessage writeMessageResponse;
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	writeMessageResponse.FromBuffer(runner);
	std::cout << "status: " << writeMessageResponse.GetStatus() << std::endl;
	delete[] sendBuff;
}

void TestReadMessageResponse()
{
	std::cout << "TestReadMessageResponse" << std::endl;
	auto data = std::shared_ptr<char[]>(new char[8]{"bla bla"});
	ilrd::ReadResponseMessage readMessageResp(ilrd::UID(), true, data.get(), 8);
	auto sendBuff = new char[readMessageResp.GetSize()];
	readMessageResp.ToBuffer(sendBuff);
	ilrd::ReadResponseMessage readMessageRecieved;
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	readMessageRecieved.FromBuffer(runner);
	std::cout << "length: " << readMessageRecieved.GetLength() << std::endl;
	std::cout << "buffer: " << readMessageRecieved.GetBuffer() << std::endl;
	delete[] sendBuff;
}

int main()
{
	TestReadMessageSend();
	TestWriteMessageSend();
	TestReadMessageResponse();
	TestWriteMessageResponse();
	PASS;

	return 0;
}

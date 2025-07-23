/**
* @file: TestReactor.cpp
* @author: Ofir Nahshoni
* @brief: This is a file to test the Reactor API.
*/

#include <thread>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "Reactor.hpp"              // Reactor
#include "Handleton.hpp"            // Handleton
#include "UDPSocket.hpp"            // UDPSocket
#include "LinuxListener.hpp"        // LinuxListener
#include "TCPListenerSocket.hpp"    // TCPListenerSocket, TCPConnSocket

void ReadFunc(int fd, ilrd::Mode mode);
void WriteFunc(int fd, ilrd::Mode mode);
void StopFunc(ilrd::Reactor& reactor);

void SanityTestsReadWriteReactor();
void TestsForUDPListener();
void TestsForUDPClient();
void TestsForTCPListener();

int main()
{
    // SanityTestsReadWriteReactor();
    // TestsForUDPListener();
    // TestsForUDPClient();
    TestsForTCPListener();
    
    return 0;
}

void ReadFunc(int fd, ilrd::Mode mode)
{
    (void)mode;
    char buffer[BUFSIZ] = {0};

    ssize_t bytesRead = read(fd, buffer, BUFSIZ);

    if (bytesRead > 0)
    {
        std::cout << "Received from FIFO: " << buffer << std::endl;
        ilrd::Handleton::GetInstance<ilrd::Reactor>()->Unregister(fd, mode);
    }
    else if (bytesRead == -1 && errno != EAGAIN)
    {
        perror("read");
    }
}


void WriteFunc(int fd, ilrd::Mode mode)
{
    (void)mode;
    std::string msg = "received massge\n";

    if (write(fd, msg.c_str(), msg.size()) == -1)
    {
        std::cerr << "write() failed" << std::endl;
    }
}

void StopFunc(ilrd::Reactor& reactor)
{
    reactor.Register(STDIN_FILENO, ilrd::Mode::READ, 
        [&reactor](int, ilrd::Mode) 
        { 
            std::string str;
            std::cin >> str;
            
            if (str == "quit")
            {
                reactor.Stop();
            }
        });
}

void SanityTestsReadWriteReactor()
{
    const char* fifoPath = "/home/ofirnah/Desktop/Projects/IOTDrive/framework/"
                                                    "test/reactor_files/fifo1";
    const char* writefilePath = "/home/ofirnah/Desktop/Projects/IOTDrive/"
                                "framework/test/reactor_files/writefile1.txt";

    // Open the FIFO for reading (non-blocking)
    int rfd = open(fifoPath, O_RDONLY | O_NONBLOCK);
    if (rfd == -1)
    {
        perror("open fifo for read failed");
        return;
    }

    // Open the writefile for writing
    int wfd = open(writefilePath, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (wfd == -1)
    {
        perror("open writefile for write failed");
        close(rfd);
        return;
    }

    ilrd::Reactor reactor(std::make_unique<ilrd::LinuxListener>());

    reactor.Register(rfd, ilrd::Mode::READ, ReadFunc);
    // reactor.Register(wfd, ilrd::Mode::WRITE, WriteFunc);
    StopFunc(reactor);

    std::thread writerThread([fifoPath]() {
        sleep(1);
        int wfd = open(fifoPath, O_WRONLY);
        if (wfd == -1)
        {
            perror("open fifo for write failed");
            return;
        }

        const char* msg = "Hello from FIFO!\n";
        write(wfd, msg, strlen(msg));
        close(wfd);
    });

    WriteFunc(wfd, ilrd::Mode::WRITE);
    reactor.Run();

    writerThread.join();
    close(rfd);
    close(wfd);
}

void TestsForUDPListener()
{
    std::string portNum("5005");
    ilrd::UDPSocket udpListener(portNum, true);

    ilrd::Reactor reactor(std::make_unique<ilrd::LinuxListener>());

    reactor.Register(udpListener.GetFD(), ilrd::Mode::READ,
        [&udpListener](int, ilrd::Mode) {
            char buffer[BUFSIZ];
            udpListener.Receive(buffer, BUFSIZ);
            std::cout << "message received: " << buffer << std::endl;
        });

    StopFunc(reactor);
    reactor.Run();
}

void TestsForUDPClient()
{
    std::string serverPort("5000");
    std::string serverIP("127.0.0.1");
    ilrd::UDPSocket udpClient("5001");

    udpClient.SetTargetAddr(serverPort, serverIP);

    ilrd::Reactor reactor(std::make_unique<ilrd::LinuxListener>());

    reactor.Register(udpClient.GetFD(), ilrd::Mode::WRITE,
        [&udpClient, &reactor](int fd, ilrd::Mode mode) {
            const char* msg = "ping";
            udpClient.Send(msg, strlen(msg) + 1);
            std::cout << "Sent: " << msg << std::endl;
            reactor.Unregister(fd, mode);
        });

    StopFunc(reactor);
    reactor.Run();
}

void TestsForTCPListener()
{
    std::string portNum("5001");
    ilrd::TCPListenerSocket tcpListener(portNum, 5);

    ilrd::Reactor reactor(std::make_unique<ilrd::LinuxListener>());

    reactor.Register(tcpListener.GetFD(), ilrd::Mode::READ,
        [&tcpListener](int, ilrd::Mode) {
            std::unique_ptr<ilrd::TCPConnSocket> newConn = tcpListener.Accept();

            for (size_t i = 0; i < 5; ++i)
            {
                char buffer[BUFSIZ];
                newConn->Receive(buffer, BUFSIZ);
                std::cout << "Received: " << buffer << std::endl;
            }
        });

    StopFunc(reactor);
    reactor.Run();
}

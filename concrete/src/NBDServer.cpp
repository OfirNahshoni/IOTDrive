/**
* @file: NBDServer.cpp
* @author: Ofir Nahshoni
* @brief: This is a header that defines the API of NBDServer.
*/

#include <memory>
#include <csignal>
#include <fcntl.h>
#include <unistd.h>
#include <linux/nbd.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

#include "Logger.hpp"
#include "NBDServer.hpp"

int ilrd::NBDServer::m_nbdToRemove = -1;

ilrd::NBDServer::NBDServer(const std::string& devicePath, size_t deviceSize) :
                                    m_fdDevice(open(devicePath.c_str(), O_RDWR))
{
    if (m_fdDevice == -1)
    {
        throw std::runtime_error("failed in open()");
    }
    
    Init(deviceSize);

    const pid_t pid = fork();

    if (pid == -1)
    {
        throw std::runtime_error("failed in fork()");
    }

    if (pid == 0)
    {
        NBDClient();
    }

    m_nbdToRemove = static_cast<int>(m_fdDevice);
    struct sigaction act{};
    act.sa_handler = RemoveNBDConn;
    act.sa_flags = SA_RESTART;

    if (sigemptyset(&act.sa_mask) != 0)
    {
        throw std::runtime_error("failed in sigemptyset()");
    }

    if (sigaddset(&act.sa_mask, SIGINT) != 0)
    {
        throw std::runtime_error("failed in sigaddset()");
    }

    if (sigaction(SIGINT, &act, nullptr) != 0)
    {
        throw std::runtime_error("failed in sigaction()");
    }

    if (sigaction(SIGTERM, &act, nullptr) != 0)
    {
        throw std::runtime_error("failed in sigaction()");
    }
}

ilrd::NBDServer::~NBDServer()
{
    close(m_fdDevice);
}

ilrd::TCPConnSocket& ilrd::NBDServer::GetTCPSocket()
{
    return m_nbdServerSocket.value();
}

#ifdef WORDS_BIGENDIAN
uint64_t ilrd::NBDServer::Ntohll(const uint64_t a_)
{
    return a_;
}
#else
uint64_t ilrd::NBDServer::Ntohll(const uint64_t a_)
{
    uint32_t lo = a_ & 0xffffffff;
    uint32_t hi = a_ >> 32U;
    lo = ntohl(lo);
    hi = ntohl(hi);
    return static_cast<uint64_t>(lo) << 32U | hi;
}
#endif

void ilrd::NBDServer::NBDClient() const
{
    sigset_t sigset;

    if (sigfillset(&sigset) != 0)
    {
        throw std::runtime_error("failed in sigfillset()");
    }

    if (sigprocmask(SIG_SETMASK, &sigset, nullptr) != 0)
    {
        throw std::runtime_error("failed in sigprocmask()");
    }

    if (ioctl(static_cast<int>(m_fdDevice), NBD_SET_SOCK, static_cast<int>(
                                            m_nbdClientSocket.value())) == -1)
    {
        throw std::runtime_error("failed in ioctl1()");
    }

    if (ioctl(static_cast<int>(m_fdDevice), NBD_DO_IT) == -1)
    {
        throw std::runtime_error("failed in ioctl2()");
    }

    if (ioctl(static_cast<int>(m_fdDevice), NBD_CLEAR_QUE) == -1)
    {
        throw std::runtime_error("failed in ioctl3()");
    }

    if (ioctl(static_cast<int>(m_fdDevice), NBD_CLEAR_SOCK) == -1)
    {
        throw std::runtime_error("failed in ioctl4()");
    }

    exit(EXIT_SUCCESS);
}

void ilrd::NBDServer::Init(size_t deviceSize)
{
    int sockets[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) != 0)
    {
        throw std::runtime_error("failed in socketpair()");
    }

    m_nbdServerSocket.emplace(sockets[0]);
    m_nbdClientSocket.emplace(sockets[1]);

    if (ioctl(static_cast<int>(m_fdDevice), NBD_CLEAR_SOCK) == -1)
    {
        throw std::runtime_error("failed in ioctl11()");
    }

    if (ioctl(static_cast<int>(m_fdDevice), NBD_SET_SIZE, deviceSize) == -1)
    {
        throw std::runtime_error("failed in ioctl12()");
    }
}

void ilrd::NBDServer::RemoveNBDConn(int signalNum)
{
    (void)signalNum;

    if (m_nbdToRemove != -1)
    {
        if (ioctl(m_nbdToRemove, NBD_DISCONNECT) == -1)
        {
            Handleton::GetInstance<Logger>()->Log("failed to disconnect on"
                                                "NBD device", Logger::WARNING);
        }
        else
        {
            m_nbdToRemove = -1;
            Handleton::GetInstance<Logger>()->Log("request to disconnect NBD"
                                                "was sent", Logger::WARNING);
        }
    }
}
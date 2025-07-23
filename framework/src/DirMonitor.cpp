/**
* @file: DirMonitor.cpp
* @author: Ofir Nahshoni
* @brief: This source file implements the API functions of DirMonitor.hpp.
* @reviewer: Gil
* @status: APPROVED
*/

#include <climits>          // NAME_MAX

#include "DirMonitor.hpp"   // ilrd::DirMonitor

ilrd::DirMonitor::DirMonitor(const std::string& dirPath): m_isRunning(true),
                                                        m_dirPath(dirPath)
{
    m_fd = inotify_init();

    if (m_fd < 0)
    {
        throw std::runtime_error("failed to init inotify_init()");
    }

    m_wd = inotify_add_watch(m_fd, dirPath.c_str(), IN_CLOSE_WRITE | IN_DELETE);

    if (m_wd < 0)
    {
        throw std::runtime_error("failed in inotify_add_watch()");
    }
}

ilrd::DirMonitor::~DirMonitor()
{
    m_isRunning = false;
    inotify_rm_watch(m_fd, m_wd);
    m_workerThread.join();
    close(m_wd);
    close(m_fd);
}

void ilrd::DirMonitor::RegisterLoad(ACallback<const std::string&>* callback)
{
    m_loadDispatcher.Register(callback);
}

void ilrd::DirMonitor::RegisterUnload(ACallback<const std::string&>* callback)
{
    m_unloadDispatcher.Register(callback);
}

void ilrd::DirMonitor::Run()
{
    m_workerThread = std::thread(&ilrd::DirMonitor::ThreadFunc, this);
}

void ilrd::DirMonitor::ThreadFunc()
{
    while (m_isRunning)
    {
        const size_t bufferSize = sizeof(inotify_event) + NAME_MAX + 1;
        char buffer[bufferSize];
        const inotify_event* ie;

        ssize_t readSize = read(m_fd, &buffer, bufferSize);

        for (char* ptr = buffer; ptr < buffer + readSize;
            ptr += sizeof(inotify_event) + ie->len)
        {
            ie = reinterpret_cast<inotify_event*>(ptr);

            if (ie->mask & IN_CLOSE_WRITE)
            {
                m_loadDispatcher.Notify(m_dirPath + ie->name);
            }
            
            else if (ie->mask & IN_DELETE)
            {
                m_unloadDispatcher.Notify(m_dirPath + ie->name);
            }
        }
    }
}
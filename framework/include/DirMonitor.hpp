/**
* @file: DirMonitor.hpp
* @author: Ofir Nahshoni
* @brief: This header file defines the API for Directory Monitor. It detects,
* the addition of a plugin (DLL), and immediately load and execute all its
* methods.
* @reviewer: Shani
* @status: APPROVED
*/

#ifndef ILRD_RD1645_DIR_MONITOR
#define ILRD_RD1645_DIR_MONITOR

#include <string>                   // std::string
#include <thread>                   // std::jthread
#include <sys/inotify.h>            // inotify_init, inotify_add_watch

#include "DispatchCallback.hpp"     // ACallback<Event>, Dispatcher<Event>

namespace ilrd
{

class DirMonitor
{
public:
    explicit DirMonitor(const std::string& dirPath = "./plugins");
    ~DirMonitor();
    void RegisterLoad(ACallback<const std::string&>* callback);
    void RegisterUnload(ACallback<const std::string&>* callback);
    void Run();

private:
    int m_fd;
    int m_wd;
    bool m_isRunning;
    std::string m_dirPath;
    Dispatcher<const std::string&> m_loadDispatcher;
    Dispatcher<const std::string&> m_unloadDispatcher;
    std::thread m_workerThread;

    void ThreadFunc();
};  // class DirMonitor

}   // namespace ilrd

#endif  // ILRD_RD1645_DIR_MONITOR
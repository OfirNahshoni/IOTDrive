/**
* @file: Logger.hpp
* @author: Ofir Nahshoni
* @brief: This is an API header file for Logger. Note that you should use
* Handleton to write to single-instance of Logger. The Ctor is encapsulated.
* @reviewer: Shani
* @status: APPROVED
*/

#ifndef ILRD_RD1645_LOGGER_HPP
#define ILRD_RD1645_LOGGER_HPP

#include <string>               // std::string
#include <thread>               // std:jthread
#include <fstream>              // std::fstream

#include "Handleton.hpp"        // Handleton
#include "TSWaitableQueue.hpp"  // TSWaitableQueue<T, DS>

namespace ilrd
{

class Logger
{
public:
    friend class ilrd::Handleton;
    enum Severity
    {
        DEBUG,
        WARNING,
        ERROR,
        NUM_OF_SEVERITIES
    };

    ~Logger();
    void Log(const std::string& msg, Severity severity = DEBUG);
    
private:
    struct msgItem;
    bool m_isRunning;
    std::fstream m_fs;
    std::string m_severityLUT[NUM_OF_SEVERITIES];
    TSWaitableQueue<ilrd::Logger::msgItem> m_msgQueue;
    std::jthread m_wthread;     // initialized after the Queue initialized
    
    Logger();
    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& rhs) = delete;

    void WorkerThread();
    std::string GetTimeAndDate();

    struct msgItem
    {
        std::string m_timestamp;
        std::string m_msg;
        Severity m_severity;
    };
};

}   // namespace ilrd

#endif  // ILRD_RD1645_LOGGER_HPP

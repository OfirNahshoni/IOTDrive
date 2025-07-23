/**
* @file: Logger.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API Logger.hpp.
* @reviewer: Shani
* @status: APPROVED
*/

#include <iomanip>          // put_time
#include <ctime>            // localtime
#include <sstream>          // stringstream
#include <chrono>           // std::chrono:system_clock

#include "Logger.hpp"       // Logger


/*-------------------public functions implementations-------------------------*/
void ilrd::Logger::Log(const std::string& msg, Severity severity)
{
    msgItem msgObject = { GetTimeAndDate(), msg, severity };
    m_msgQueue.Push(msgObject);
}


/*------------------private functions implementations-------------------------*/
ilrd::Logger::Logger(): m_isRunning(true), 
                        m_fs("log.txt", std::ios::out), 
                        m_severityLUT{"DEBUG", "WARNING", "ERROR"},
                        m_wthread([this] { WorkerThread(); })
{ }

ilrd::Logger::~Logger()
{
    m_isRunning = false;
    Log("EXITING");
}

void ilrd::Logger::WorkerThread()
{
    while (!m_msgQueue.IsEmpty() || m_isRunning)
    {
        msgItem msgObject;

        m_msgQueue.Pop(msgObject);

        m_fs << msgObject.m_timestamp << " | "
            << msgObject.m_msg << " | "
            << m_severityLUT[msgObject.m_severity] << std::endl;
    }
}

std::string ilrd::Logger::GetTimeAndDate()
{
    std::stringstream strStream;
    auto nowTime = std::chrono::system_clock::now();
    auto inTimeT = std::chrono::system_clock::to_time_t(nowTime);

    strStream << std::put_time(std::localtime(&inTimeT), "%Y/%m/%d, %X");

    return strStream.str();
}

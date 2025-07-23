/**
* @file: FileManager.cpp
* @author: Ofir Nahshoni
* @brief: This is a source file that implements the API FileManager. it 
* implements the operations of read and write, that actually read or write
* to a file with a regular array.
*/

#include <iostream>

#include "FileManager.hpp"

void ilrd::FileManager::Init(const std::string& path)
{
    m_fs.open(path);

    if (m_fs.bad())
    {
        throw std::runtime_error("failed to open fstream in FileManager");
    }
}

bool ilrd::FileManager::Read(size_t offset, size_t length, char* outBuffer)
{
    std::unique_lock lock(m_mutex);
    m_fs.seekg(offset);
    m_fs.read(outBuffer, length);

    std::cout << "status good(): " << m_fs.good() << std::endl;
    
    return m_fs.good();
}

bool ilrd::FileManager::Write(size_t offset, size_t length, 
                                                std::shared_ptr<char[]> buffer)
{
    std::unique_lock lock(m_mutex);
    m_fs.seekp(offset);
    m_fs.write(buffer.get(), length);
    m_fs.flush();
    std::cout << "status good(): " << m_fs.good() << std::endl;
    
    return m_fs.good();
}
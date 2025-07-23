/**
* @file: Handleton.cpp
* @author: Ofir Nahshoni
* @brief: A source file for the header HAndleton.hpp.
*/

#include "Handleton.hpp"

std::mutex ilrd::Handleton::m_mutex;
std::unordered_map<const std::type_info*, std::shared_ptr<void>, 
                ilrd::Handleton::HashFunc, 
                ilrd::Handleton::Comparator> ilrd::Handleton::m_symbols;
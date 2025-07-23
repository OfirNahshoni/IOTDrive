# concrete/src/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(Concrete)

add_library(concrete_static STATIC AMessage.cpp ATaskArgs.cpp MinionManager.cpp
            MinionProxy.cpp NBDProxy.cpp NBDServer.cpp ReadCommand.cpp
            WriteCommand.cpp ReadResponse.cpp WriteResponse.cpp TaskResult.cpp
            Ticket.cpp ResponseManager.cpp)
target_link_libraries(concrete_static framework_static udp_static tcp_static)

add_library(concrete_minion_static STATIC AMessage.cpp ATaskArgs.cpp
            MasterProxy.cpp UID.cpp FileManager.cpp MasterProxy.cpp
            Minion_ReadCommand.cpp Minion_ReadTaskArgs.cpp
            Minion_WriteCommand.cpp Minion_WriteTaskArgs.cpp)
target_link_libraries(concrete_minion_static framework_static listener_static
                        udp_static)

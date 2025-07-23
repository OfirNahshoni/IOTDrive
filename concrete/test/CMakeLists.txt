# concrete/test/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(Concrete)

add_executable(concrete TestMaster.cpp)
target_link_libraries(concrete concrete_static)

add_executable(concrete_minion1 TestDemoMinion1.cpp)
target_link_libraries(concrete_minion1 concrete_minion_static)

add_executable(file_creator Create8MBFile.cpp)

add_executable(concrete_minion2 TestDemoMinion2.cpp)
target_link_libraries(concrete_minion2 concrete_minion_static)

#add_executable(concrete_pi TestMinionRaspberry.cpp)
#target_link_libraries(concrete_pi concrete_minion_static)

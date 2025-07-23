# concrete/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(Concrete)

include_directories(include)
include_directories(../framework/include)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

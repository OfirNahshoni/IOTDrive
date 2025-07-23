# top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(IOTDrive)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "-pedantic-errors -Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall -Werror -Wextra")
set(CMAKE_C_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")

add_subdirectory(concrete)
add_subdirectory(framework)

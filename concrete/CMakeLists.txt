# concrete/CMakeLists.txt

project(Concrete)

include_directories(include ${CMAKE_SOURCE_DIR}/framework/include)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

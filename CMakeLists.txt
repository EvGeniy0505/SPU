cmake_minimum_required(VERSION 3.5)
project(SPU CXX)

add_subdirectory(Stack)
add_subdirectory(Onegin)

set(SOURCE "compiller.cpp" "processor.cpp" "main.cpp")

add_executable(processor ${SOURCE})

target_link_libraries(processor stack)
target_link_libraries(processor file_read)

target_include_directories(processor PRIVATE Stack)
target_include_directories(processor PRIVATE Onegin)
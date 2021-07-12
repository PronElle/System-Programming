cmake_minimum_required(VERSION 3.14)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5 main.cpp CountingSemaphore.h mylockguard.h)
target_link_libraries(Lab5 pthread)
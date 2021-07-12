cmake_minimum_required(VERSION 3.14)
project(Lab6)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab6 main.cpp myptask.h threadpool.h dynamic_pool.h)
target_link_libraries(Lab6 pthread)
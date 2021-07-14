cmake_minimum_required(VERSION 3.14)
project(exams)

set(CMAKE_CXX_STANDARD 17)

add_executable(exams main.cpp Joiner.h CBuffer.h SingleThreadExecutor.h Exchanger.h raii_guard.h)
target_link_libraries(exams pthread)
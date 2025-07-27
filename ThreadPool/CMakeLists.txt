#最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

#项目名称
project(ThreadPool)

#C++标准
set(CMAKE_CXX_STANDARD 11)

#可执行文件及源文件
add_executable(ThreadPool TaskQueue.cpp ThreadPool.cpp Test.cpp)

cmake_minimum_required(VERSION 3.26)
project(BuggyAutoSAR)


set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE core_files ./*.hpp)
file(GLOB_RECURSE com_files ./*.hpp)
add_executable(BuggyAutoSAR main.cpp ${core_files})
target_include_directories(BuggyAutoSAR PRIVATE .)

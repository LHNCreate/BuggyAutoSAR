cmake_minimum_required(VERSION 3.26)
project(BuggyAutoSAR)


set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE core_files ./*.hpp)
file(GLOB_RECURSE com_files ./*.hpp)




add_executable(BuggyAutoSAR main.cpp ${core_files})
# folly
find_package(folly CONFIG REQUIRED)
target_link_libraries(BuggyAutoSAR PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

#spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(BuggyAutoSAR PRIVATE spdlog::spdlog)


target_include_directories(BuggyAutoSAR PRIVATE .)

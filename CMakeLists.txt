cmake_minimum_required(VERSION 3.22)
project(BuggyAutoSAR)


set(CMAKE_CXX_STANDARD 20)

#ara_core
add_subdirectory(core)
#ara_com
add_subdirectory(com)


# BuggyAutoSAR
add_executable(BuggyAutoSAR main.cpp)
target_link_libraries(BuggyAutoSAR PRIVATE ara_core ara_com)

#NetWorkBinding(iceoryx)
find_package(iceoryx_binding_c CONFIG REQUIRED)
target_link_libraries(BuggyAutoSAR PRIVATE iceoryx_binding_c::iceoryx_binding_c)

#find_package(iceoryx_hoofs CONFIG REQUIRED)
#target_link_libraries(BuggyAutoSAR PRIVATE iceoryx_hoofs::iceoryx_hoofs
#        iceoryx_hoofs::iceoryx_platform)
#
#find_package(iceoryx_posh CONFIG REQUIRED)
#target_link_libraries(BuggyAutoSAR PRIVATE iceoryx_posh::iceoryx_posh
#        iceoryx_posh::iceoryx_posh_roudi
#        iceoryx_posh::iceoryx_posh_config
#        iceoryx_posh::iceoryx_posh_gateway)
# folly
#find_package(folly CONFIG REQUIRED)
#target_link_libraries(BuggyAutoSAR PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

#spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(BuggyAutoSAR PRIVATE spdlog::spdlog)


target_include_directories(BuggyAutoSAR PRIVATE .)


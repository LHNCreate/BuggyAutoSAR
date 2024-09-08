cmake_minimum_required(VERSION 3.22)

file(GLOB_RECURSE core_files ./*.hpp)

add_library(ara_core INTERFACE ${core_files})

set_target_properties(ara_core PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
target_include_directories(ara_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
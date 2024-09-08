cmake_minimum_required(VERSION 3.22)

file(GLOB_RECURSE com_files ./*.hpp)

add_library(ara_com INTERFACE ${com_files})

set_target_properties(ara_com PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
target_include_directories(ara_com INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
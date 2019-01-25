project(tm_tests)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17")

include_directories(/home/athomps/dev)
include_directories(/home/athomps/libs/include)

add_executable(tm_tests
    main.cpp
    add_const_ref_ut.cpp
    replace_type_ut.cpp
)


cmake_minimum_required(VERSION 3.0.0)
project(Syroot VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_library(Syroot Syroot.cpp)


target_include_directories(Syroot PUBLIC
    src)

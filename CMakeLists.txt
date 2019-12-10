cmake_minimum_required(VERSION 3.13)
project(network_sim)

set(CMAKE_CXX_STANDARD 14)

add_executable(network_sim main.cpp include/package.hpp include/types.hpp include/storage_types.hpp src/package.cpp src/storage_types.cpp)
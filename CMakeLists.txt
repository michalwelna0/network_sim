cmake_minimum_required(VERSION 3.13)
project(network_sim)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp)

add_executable(network_sim_debug ${SOURCE_FILES} main.cpp )

#--- Unit testing using Google Testing Framework ---

set(SOURCE_FILES_TESTS
        test/test_package.cpp
        test/test_storage_types.cpp
        test/test_nodes.cpp)

add_executable(network_sim_test ${SOURCE_FILES_TESTS} ${SOURCE_FILES} test/main_test.cpp)

target_include_directories(network_sim_test PUBLIC
        ../googletest-master/googlemock/include
        ../googletest-master/googletest/include
        )

add_subdirectory(../googletest-master googletest-master)

target_link_libraries(network_sim_test gmock)


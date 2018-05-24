cmake_minimum_required(VERSION 3.0)
project(durian)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

add_subdirectory(googletest/)

set(SOURCE_FILES
        src/main.cpp)

set(TEST_FILES
        test/main.cpp)

add_executable(durian
        ${SOURCE_FILES})

add_executable(durian_test
        ${TEST_FILES})
target_link_libraries(durian_test gtest_main)
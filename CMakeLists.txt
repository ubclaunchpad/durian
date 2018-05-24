cmake_minimum_required(VERSION 3.0)
project(durian)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

set(SOURCE_FILES
        src/main.cpp)

add_executable(durian
        ${SOURCE_FILES})
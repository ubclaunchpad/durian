cmake_minimum_required(VERSION 3.0)
project(durian)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

add_executable(VM
        ${PROJECT_SOURCE_DIR}/src/interpreter/main.cpp
        ${PROJECT_SOURCE_DIR}/src/interpreter/vm/VM.cpp
        ${PROJECT_SOURCE_DIR}/src/interpreter/vm/DurianObject.cpp)

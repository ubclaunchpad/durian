cmake_minimum_required(VERSION 3.0)
project(durian)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/include)

add_executable(VM
        src/interpreter/main.cpp
        src/interpreter/vm/DurianObject.cpp
        src/interpreter/vm/VM.cpp)

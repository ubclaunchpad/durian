cmake_minimum_required(VERSION 3.10)
project(durian)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/include)

add_executable(durian
        src/include/DurianObject.h
        src/include/opcode.h
        src/include/VM.h
        src/interpreter/vm/VM.cpp src/interpreter/vm/DurianObject.cpp)

cmake_minimum_required(VERSION 3.10)
project(durian)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

add_subdirectory(googletest/)

set(SOURCE_FILES
        src/lexer/Lexer.cpp
        src/interpreter/vm/VM.cpp)

set(TEST_FILES
        test/main.cpp src/include/DurianObject.h)

add_executable(durian
        src/include/DurianObject.h
        src/include/opcode.h
        src/include/VM.h
        src/interpreter/vm/VM.cpp src/interpreter/vm/DurianObject.cpp)

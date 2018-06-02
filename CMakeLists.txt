cmake_minimum_required(VERSION 3.0)
project(durian)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/include)

add_subdirectory(googletest/)

set(SOURCE_FILES
        src/lexer/Lexer.cpp
        src/interpreter/vm/VM.cpp)

set(TEST_FILES
        test/main.cpp src/include/DurianObject.h)

set(TEST_FILES
        test/TestLexer.cpp)

add_executable(VM
        src/interpreter/main.cpp
        src/interpreter/vm/DurianObject.cpp
        src/interpreter/vm/VM.cpp)

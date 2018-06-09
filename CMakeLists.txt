cmake_minimum_required(VERSION 3.0)
project(durian)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/include)

add_subdirectory(googletest/)

set(SOURCE_FILES
        src/lexer/Lexer.cpp
        src/parser/Parser.cpp)

set(TEST_FILES
        test/TestLexer.cpp test/TestParser.cpp)

add_executable(VM
        src/interpreter/main.cpp
        src/interpreter/vm/DurianObject.cpp
        src/interpreter/vm/VM.cpp)

add_executable(durian_test
        ${SOURCE_FILES}
        ${TEST_FILES})

target_link_libraries(durian_test gtest_main)
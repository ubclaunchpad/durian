cmake_minimum_required(VERSION 3.0)
project(durian LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src/include)

add_subdirectory(googletest/)

set(SOURCE_FILES
        src/lexer/Lexer.cpp
        src/parser/Parser.cpp
        src/pretty_printer/PrettyPrinter.cpp)

set(TEST_FILES
        test/TestLexer.cpp test/TestParser.cpp)

add_executable(VM
        src/interpreter/main.cpp
        src/interpreter/vm/DurianObject.cpp
        src/interpreter/vm/VM.cpp)

add_executable(pretty_printer
        src/pretty_printer/main.cpp
        ${SOURCE_FILES})

add_executable(durian_test
        ${SOURCE_FILES}
        ${TEST_FILES})

target_link_libraries(durian_test gtest_main)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(VM PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(VM PRIVATE -Wexit-time-destructors -Wmissing-noreturn )
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(VM PRIVATE /W4 /w44265 /w44061 /w44062 )
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(durian_test PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(durian_test PRIVATE -Wexit-time-destructors -Wmissing-noreturn )
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(durian_test PRIVATE /W4 /w44265 /w44061 /w44062 )
endif()

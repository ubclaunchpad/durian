cmake_minimum_required(VERSION 3.0)
project(durian LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src/include)

add_subdirectory(googletest/)

set(SOURCE_FILES
        src/compiler/Compiler.cpp
        src/lexer/Lexer.cpp
        src/parser/Parser.cpp
        src/pretty_printer/PrettyPrinter.cpp
        src/vm/DurianObject.cpp
        src/vm/VM.cpp
        src/treewalk/Interpreter.cpp)

set(TEST_FILES
        test/TestLexer.cpp test/TestParser.cpp)

add_executable(durian
        src/main.cpp
        ${SOURCE_FILES})

add_executable(durian_test
        ${SOURCE_FILES}
        ${TEST_FILES})
target_link_libraries(durian_test gtest_main)

if (DEFINED ENV{DURIAN_COVERAGE})
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    setup_target_for_coverage(NAME ${PROJECT_NAME}_coverage durian_test coverage)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(durian PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(durian PRIVATE -Wexit-time-destructors -Wmissing-noreturn)
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(durian PRIVATE /W4 /w44265 /w44061 /w44062)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(durian_test PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(durian_test PRIVATE -Wexit-time-destructors -Wmissing-noreturn)
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(durian_test PRIVATE /W4 /w44265 /w44061 /w44062)
endif ()

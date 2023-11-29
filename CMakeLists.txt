cmake_minimum_required(VERSION 3.26)
project(esoterics)

add_subdirectory(lib/googletest)

add_executable(esoterics)
add_executable(esoterics_tests)

target_sources(esoterics PRIVATE
        src/main.cpp
        src/brainfuck/Brainfuck.cpp
        src/brainfuck/Translator.cpp
        src/brainfuck/Memory.cpp
        src/common/File.cpp
)

target_sources(esoterics_tests PRIVATE
        src/brainfuck/Brainfuck.cpp
        src/brainfuck/Memory.cpp
        src/common/File.cpp
        tests/common/File_Test.cpp
        tests/brainfuck/Memory_Test.cpp
        tests/brainfuck/Brainfuck_Test.cpp
        src/brainfuck/Translator.cpp
)

target_include_directories(esoterics PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brainfuck
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brainfuck
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common
)

target_include_directories(esoterics_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/brainfuck
        ${CMAKE_CURRENT_SOURCE_DIR}/include/brainfuck
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common
)

target_link_libraries(esoterics)
target_link_libraries(esoterics_tests gtest gtest_main)

set_target_properties(esoterics esoterics_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

add_custom_target(runUnitTests
    COMMAND esoterics_tests DEPENDS esoterics_tests
)
cmake_minimum_required(VERSION 3.12)

project(smolTankeryGame) 

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

enable_testing()
include_directories(src)
add_subdirectory(tests)
add_test(smolTankeryGame ${CMAKE_BINARY_DIR}/bin/smolTankeryGame_tests)


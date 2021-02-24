cmake_minimum_required(VERSION 3.10)

project(huc VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

enable_testing()

include_directories($(HUC_SOURCE_DIR)/include)

add_subdirectory(src)

add_subdirectory(tests)
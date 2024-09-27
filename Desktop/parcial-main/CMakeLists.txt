cmake_minimum_required(VERSION 3.15)
project(MyUnrealProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/Source)
file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h")

add_executable(MyUnrealProject ${SOURCES})

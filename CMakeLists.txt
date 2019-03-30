cmake_minimum_required (VERSION 3.8)

project(RubiksCube)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/eigen)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/boost)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/rang/include)

file(GLOB SOURCES src/*.cpp)
add_executable(RubiksCube ${SOURCES})

if (UNIX)
    if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(RubiksCube PRIVATE -std=c++11 -Wall -Ofast)
    endif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
endif (UNIX)

if (MSVC)
    if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(RubiksCube PRIVATE /O2)
    endif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
endif (MSVC)

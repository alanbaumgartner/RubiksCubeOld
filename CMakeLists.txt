cmake_minimum_required (VERSION 3.8)

project(RubiksCube)

#set (CMAKE_PREFIX_PATH "C:\\Qt\\5.12.2\\msvc2017_64\\")

find_package(Qt5Widgets)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/eigen)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/boost)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/rang/include)

file(GLOB SOURCES src/*.cpp)

if (UNIX)
    add_executable(RubiksCube ${SOURCES})
    if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(RubiksCube PRIVATE -std=c++17 -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wold-style-cast -Wuseless-cast -Wjump-misses-init -Wdouble-promotion -Wshadow -Wformat=2 -Ofast)
    endif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
endif (UNIX)

if (MSVC)
    add_executable(RubiksCube WIN32 ${SOURCES})
    if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(RubiksCube PRIVATE /O2)
    endif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
endif (MSVC)

target_link_libraries (RubiksCube Qt5::Widgets)

install(SCRIPT bundle.cmake)
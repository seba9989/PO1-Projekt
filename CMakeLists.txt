cmake_minimum_required(VERSION 3.15)
project(SpaceInvaders CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(SpaceInvaders ${SOURCES})

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

target_link_libraries(SpaceInvaders PRIVATE raylib)

if (APPLE)
    find_library(IOKIT IOKit)
    find_library(COCOA Cocoa)
    find_library(OPENGL OpenGL)
    target_link_libraries(SpaceInvaders PRIVATE ${IOKIT} ${COCOA} ${OPENGL})
elseif (UNIX AND NOT APPLE)
    target_link_libraries(SpaceInvaders PRIVATE m pthread dl)
endif()

if (WIN32)
    target_link_libraries(SpaceInvaders PRIVATE opengl32 gdi32 winmm)
endif()

# This root cmake file pulls together the libraries and executables in subdirectories
cmake_minimum_required(VERSION 4.2)
project(MEGEngineProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Don't want to carry around copies of the C/C++ library DLLs with the .exe
#set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(OpenGL REQUIRED)

add_subdirectory(engine)
add_subdirectory(game)
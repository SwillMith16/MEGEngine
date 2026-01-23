# This root cmake file pulls together the libraries and executables in subdirectories
cmake_minimum_required(VERSION 4.2)
project(MEGEngineProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_subdirectory(engine)
add_subdirectory(game)
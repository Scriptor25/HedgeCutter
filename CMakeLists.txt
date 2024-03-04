cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE sources "src/**.cpp")

project(Hedgecutter)
add_executable(Hedgecutter "${sources}")

target_include_directories(Hedgecutter PUBLIC "include/")

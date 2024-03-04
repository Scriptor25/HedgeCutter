cmake_minimum_required(VERSION 3.10)

project(Hedgecutter)

file(GLOB_RECURSE sources "src/**.cpp")

add_executable(Hedgecutter "${sources}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(Hedgecutter PUBLIC "include/")

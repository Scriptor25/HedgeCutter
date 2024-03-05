cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE src "src/**.cpp")
file(GLOB_RECURSE inc "include/**.h")

project(HedgeCutter)
add_executable(HedgeCutter "${src}" "${inc}")

target_include_directories(HedgeCutter PUBLIC "include")

install(TARGETS HedgeCutter)
install(DIRECTORY "res" DESTINATION ".")


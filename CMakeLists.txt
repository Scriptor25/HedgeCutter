cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE src "src/**.cpp")

project(HedgeCutter)
add_executable(HedgeCutter "${src}" "include/hcut/lang/Stmt.h")

target_include_directories(HedgeCutter PUBLIC "include")

install(TARGETS HedgeCutter)
install(DIRECTORY "res" DESTINATION ".")


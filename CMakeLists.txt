cmake_minimum_required(VERSION 3.22)

project(structures_of_data)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE Debug)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(main ${sources})
target_compile_options(main PRIVATE -Wsuggest-override)
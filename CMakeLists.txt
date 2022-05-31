cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# SET(CMAKE_C_COMPILER clang)
# SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 14)
set(ENV{CRNT_PATH} ${CMAKE_CURRENT_SOURCE_DIR})


project(simpleDFS)

add_subdirectory(master EXCLUDE_FROM_ALL)
add_subdirectory(client EXCLUDE_FROM_ALL)
add_subdirectory(chunk_node EXCLUDE_FROM_ALL)
add_subdirectory(utils)
add_subdirectory(thirdparty/rpclib)
add_subdirectory(thirdparty/jsoncpp)
add_subdirectory(thirdparty/pico)
add_subdirectory(thirdparty/tree)
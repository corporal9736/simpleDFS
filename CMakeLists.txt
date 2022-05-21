cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# SET(CMAKE_C_COMPILER clang)
# SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 14)
set(ENV{CRNT_PATH} ${CMAKE_CURRENT_SOURCE_DIR})


project(simpleDFS)

add_subdirectory(master)
add_subdirectory(client)
add_subdirectory(chunk_node)
add_subdirectory(thirdparty/rpclib)
add_subdirectory(thirdparty/jsoncpp)
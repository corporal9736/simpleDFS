cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# SET(CMAKE_C_COMPILER clang)
# SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 14)
set(ENABLE_TESTS OFF CACHE BOOL "build st_tree tests")
set(JSONCPP_WITH_TESTS OFF CACHE BOOL "build jsoncpp tests")
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "build jsoncpp unit tests")
set(BUILD_STATIC_LIBS OFF CACHE BOOL "build jsoncpp static libs")
set(BUILD_OBJECT_LIBS OFF CACHE BOOL "build jsoncpp object libs")


project(simpleDFS)

add_subdirectory(master EXCLUDE_FROM_ALL)
add_subdirectory(client EXCLUDE_FROM_ALL)
add_subdirectory(chunk_node EXCLUDE_FROM_ALL)
add_subdirectory(utils)
add_subdirectory(thirdparty/rpclib)
add_subdirectory(thirdparty/jsoncpp)
add_subdirectory(thirdparty/pico)
add_subdirectory(thirdparty/tree)
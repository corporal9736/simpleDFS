cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(simpleDFS_master)
set(CMAKE_CXX_FLAGS -pthread)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/include/
)
AUX_SOURCE_DIRECTORY(src SOURCES)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} rpc jsoncpp_lib st_tree utils uuid)
file(COPY config.json DESTINATION ${PROJECT_BINARY_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.10)

project(utils)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

AUX_SOURCE_DIRECTORY(src SOURCES)
ADD_LIBRARY (utils ${SOURCES})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} jsoncpp_lib)
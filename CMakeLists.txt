cmake_minimum_required(VERSION 3.10)
project(RTypeCore
    VERSION 0.0.1
    DESCRIPTION "The RType Core"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

set(SRC_MAIN
    src/main.cpp
)

set(SRC
)

add_executable(${PROJECT_NAME} ${SRC} ${SRC_MAIN})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

add_custom_target(fclean
    COMMAND make clean
    COMMAND rm -f ${PROJECT_NAME}
    COMMAND rm -rf CMakeFiles
    COMMAND rm -f CMakeCache.txt
    COMMAND rm -f cmake_install.cmake
    COMMAND rm -f Makefile
)

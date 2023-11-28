cmake_minimum_required(VERSION 3.10)
project(RTypeCore
    VERSION 0.0.1
    DESCRIPTION "The RType Core"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(WIN32)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif(UNIX AND NOT APPLE)

add_subdirectory(external)

set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

set(SRC_MAIN
    src/main.cpp
)

set(SRC
    src/Components/PositionComponent.cpp
)

add_executable(${PROJECT_NAME} ${SRC} ${SRC_MAIN})

target_link_libraries(${PROJECT_NAME} asio)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/Components
)

target_link_libraries(${PROJECT_NAME} glfw)


add_custom_target(fclean
    COMMAND make clean
    COMMAND rm -f ${PROJECT_NAME}
    COMMAND rm -rf CMakeFiles
    COMMAND rm -f CMakeCache.txt
    COMMAND rm -f cmake_install.cmake
    COMMAND rm -f Makefile
)

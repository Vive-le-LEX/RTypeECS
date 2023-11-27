cmake_minimum_required(VERSION 3.10)
project(RTypeCore
    VERSION 0.0.1
    DESCRIPTION "The RType Core"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")

    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

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

target_link_libraries(${PROJECT_NAME}
    glfw
    ${GLFW_LIBRARIES}
)

add_custom_target(fclean
    COMMAND make clean
    COMMAND rm -f ${PROJECT_NAME}
    COMMAND rm -rf CMakeFiles
    COMMAND rm -f CMakeCache.txt
    COMMAND rm -f cmake_install.cmake
    COMMAND rm -f Makefile
)

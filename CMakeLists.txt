
cmake_minimum_required(VERSION 3.10)
project(rtype-ecs VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

include(external/CMakeLists.txt)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    FILES
        ${PROJECT_NAME}Config.cmake
        ${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

if (IS_TESTING AND NOT WIN32)
    include(CTest)

    message(STATUS "Building tests")
    set(TEST_PROJECT_NAME ${PROJECT_NAME}-test)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(SRC_TEST
        tests/hello.cpp
    )
    add_executable(${TEST_PROJECT_NAME} ${SRC_TEST} ${SRC})

    target_link_libraries(${TEST_PROJECT_NAME} PRIVATE GTest::gtest_main)

    target_include_directories(${TEST_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

    include(GoogleTest)
    gtest_discover_tests(${TEST_PROJECT_NAME})
endif()

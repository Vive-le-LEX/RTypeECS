cmake_minimum_required(VERSION 3.10)
project(rtype-ecs
    VERSION 1.0.0
    DESCRIPTION "RTypeECS"
    LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)


include(external/CMakeLists.txt)

set(SRC_MAIN

)

set(SRC
)


add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE include)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

install(TARGETS ${PROJECT_NAME} ${ALL_LIBRARIES} EXPORT rtype-ecs
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
export(TARGETS ${PROJECT_NAME} FILE rtype-ecs.cmake)


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

    target_include_directories(${TEST_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/RTypeECS)

    include(GoogleTest)
    gtest_discover_tests(${TEST_PROJECT_NAME})
endif()

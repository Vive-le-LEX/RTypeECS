include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE) # Needed to print downloading progress

# Download and extract the asio library from GitHub
message(STATUS "Downloading and extracting asio library sources. This will take some time...")
FetchContent_Declare(asio
    GIT_REPOSITORY git@github.com:chriskohlhoff/asio.git
    GIT_TAG master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)

FetchContent_GetProperties(asio)

if(NOT asio_POPULATED)
    FetchContent_Populate(asio)
endif()

add_library(asio INTERFACE)

target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
find_package(Threads)
target_link_libraries(asio INTERFACE Threads::Threads)

# Download and extract the glfw3 library from GitHub

message(STATUS "Downloading and extracting glfw3 library sources. This will take some time...")
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

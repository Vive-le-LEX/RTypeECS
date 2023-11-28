include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE) # Needed to print downloading progress

# Download and extract the boost library from GitHub
message(STATUS "Downloading and extracting boost library sources. This will take some time...")

FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.7z # downloading a zip release speeds up the download
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_PROGRESS TRUE
    DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

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

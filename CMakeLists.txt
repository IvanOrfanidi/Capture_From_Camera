# Version CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(capture_from_camera VERSION 1.0.0)

configure_file(
    project_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/project_version.h
)

# Option
set(CMAKE_CXX_STANDARD 17)

# Compiler-specific options
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR(CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Source files
file(GLOB_RECURSE SOURCES
    source/*.cpp
)

find_package(OpenCV REQUIRED)

# Boost components
set(BOOST_COMPONENTS
    program_options
    system
    filesystem
)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    ${Boost_LIBRARIES}
)
# CMake minimum version. Change range if using unsupported CMake version.
cmake_minimum_required(VERSION 3.14...3.27)

# Project name, description, and language (C vs. CPP).
project(milestone3
        DESCRIPTION "milestone3"
        LANGUAGES CXX)

# Set C++ version to use.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch JSON parsing library from GitHub(R).
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Declare the executable, and its name.
add_executable(milestone3
        hash_table.cpp)

# Glob all files ending in `.cpp` and compile them together.
file(GLOB SRC *.cpp)
target_sources(milestone3 PRIVATE ${SRC}
)

# Link external libraries (JSON library) to the executable.
target_link_libraries(milestone3 PRIVATE
        nlohmann_json::nlohmann_json
)

# Copy `.json` files into the build directory.
add_custom_command(TARGET milestone3 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/*.json $<TARGET_FILE_DIR:milestone3>)
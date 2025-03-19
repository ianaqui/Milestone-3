cmake_minimum_required(VERSION 3.10)
project(milestone3)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCE_FILES
        milestone3.cpp
        cache_manager.cpp
        doubly_linked_list.cpp
        hash_table.cpp
        hash_node.cpp
        dll_node.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include directory for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Copy JSON files individually to avoid wildcard issues
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/milestone3.json
        ${CMAKE_BINARY_DIR}/milestone3.json)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/milestone3_config.json
        ${CMAKE_BINARY_DIR}/milestone3_config.json)

# Enable JSON library (if it's using a vendored JSON library)
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    # Include the JSON library from the project
    include_directories(${CMAKE_SOURCE_DIR}/json)
endif()
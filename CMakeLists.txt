cmake_minimum_required(VERSION 3.28)

project(DiffQL
    VERSION 1.0.0
    DESCRIPTION "DiffQL C++20 Project"
    LANGUAGES CXX
)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create target
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)



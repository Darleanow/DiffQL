cmake_minimum_required(VERSION 3.28)
project(DiffQL
    VERSION 1.0.0
    DESCRIPTION "DiffQL C++20 Project"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(MARIADB REQUIRED mariadb)

add_library(sqlparser STATIC IMPORTED)
set_target_properties(sqlparser PROPERTIES
    IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/external/sql-parser/libsqlparser.so
)

# Create target
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/external/sql-parser/src
        ${MARIADB_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        sqlparser
        ${MARIADB_LIBRARIES}
)

# Compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

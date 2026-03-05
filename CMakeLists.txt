cmake_minimum_required(VERSION 3.28)

# Force Clang if present
find_program(CLANG_CXX_COMPILER clang++)
find_program(CLANG_C_COMPILER clang)
if(CLANG_CXX_COMPILER AND CLANG_C_COMPILER)
    set(CMAKE_C_COMPILER ${CLANG_C_COMPILER})
    set(CMAKE_CXX_COMPILER ${CLANG_CXX_COMPILER})
endif()

project(DiffQL
    VERSION 1.0.0
    DESCRIPTION "DiffQL C++20 Project"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(MARIADB REQUIRED mariadb)

# ANTLR4 C++ Runtime
include(FetchContent)

FetchContent_Declare(
    antlr4-runtime
    GIT_REPOSITORY https://github.com/antlr/antlr4.git
    GIT_TAG        4.13.2
    SOURCE_SUBDIR  runtime/Cpp
)

set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
set(ANTLR_BUILD_SHARED OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(antlr4-runtime)

# Generated ANTLR sources (separate target, no clang-tidy)
set(ANTLR_GENERATED_DIR ${PROJECT_SOURCE_DIR}/generated)

add_library(antlr4_generated STATIC
    ${ANTLR_GENERATED_DIR}/MariaDBDDLLexer.cpp
    ${ANTLR_GENERATED_DIR}/MariaDBDDLParser.cpp
    ${ANTLR_GENERATED_DIR}/MariaDBDDLParserBaseVisitor.cpp
    ${ANTLR_GENERATED_DIR}/MariaDBDDLParserVisitor.cpp
)

target_include_directories(antlr4_generated PUBLIC
    ${ANTLR_GENERATED_DIR}
)

target_link_libraries(antlr4_generated PUBLIC antlr4_static)
target_compile_options(antlr4_generated PRIVATE -w)
set_target_properties(antlr4_generated PROPERTIES CXX_CLANG_TIDY "")

# Create target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/CanonicalObjectModel/TypeNormalization/TypeMapper.cpp
    src/Connectors/MariaDB/Connector.cpp
    src/Parser/DDLVisitor.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${MARIADB_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        antlr4_generated
        ${MARIADB_LIBRARIES}
)

# Compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "clang-tidy")

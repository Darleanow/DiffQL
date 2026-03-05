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
pkg_check_modules(MARIADB mariadb)

# ANTLR4 C++ Runtime
include(FetchContent)

FetchContent_Declare(
    antlr4-runtime
    GIT_REPOSITORY https://github.com/antlr/antlr4.git
    GIT_TAG        4.13.2
    SOURCE_SUBDIR  runtime/Cpp
)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
set(ANTLR_BUILD_SHARED OFF CACHE BOOL "" FORCE)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(antlr4-runtime googletest)

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

# PostgreSQL client library (libpq)
if(APPLE)
    set(PostgreSQL_ROOT /opt/homebrew/opt/libpq)
endif()
find_package(PostgreSQL)

# Create target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/CanonicalObjectModel/TypeNormalization/TypeMapper.cpp
    src/MigrationGenerator/MigrationGenerator.cpp
    src/MigrationGenerator/MariaDBMigrationGenerator.cpp
    src/MigrationGenerator/PostgreSQLMigrationGenerator.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(PostgreSQL_FOUND)
    target_sources(${PROJECT_NAME} PRIVATE src/Connectors/PostgreSQL/Connector.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)
endif()

if(MARIADB_FOUND)
    target_sources(${PROJECT_NAME} PRIVATE
        src/Connectors/MariaDB/Connector.cpp
        src/Parser/DDLVisitor.cpp
        src/DiffEngine/DiffEngine.cpp
    )
    target_include_directories(${PROJECT_NAME} PRIVATE ${MARIADB_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE antlr4_generated ${MARIADB_LIBRARIES})
endif()

# Compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

find_program(CLANG_TIDY_EXE NAMES clang-tidy HINTS /opt/homebrew/opt/llvm/bin)
if(CLANG_TIDY_EXE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--checks=clang-diagnostic-*,clang-analyzer-*")
endif()

# Tests
enable_testing()

add_executable(DiffQL_Tests
    tests/DiffEngineTests.cpp
    src/DiffEngine/DiffEngine.cpp
)

target_include_directories(DiffQL_Tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(DiffQL_Tests
    PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(DiffQL_Tests)

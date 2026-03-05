cmake_minimum_required(VERSION 3.28)
project(DiffQL
    VERSION 1.0.0
    DESCRIPTION "DiffQL C++20 Project"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(CLANG_TIDY_BIN NAMES clang-tidy)
if(CLANG_TIDY_BIN)
  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_BIN})
endif()

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(MARIADB QUIET mariadb)
endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/external/sql-parser/libsqlparser.so)
  add_library(sqlparser SHARED IMPORTED GLOBAL)
  set_target_properties(sqlparser PROPERTIES
      IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/external/sql-parser/libsqlparser.so
  )
endif()

if(MARIADB_FOUND AND TARGET sqlparser)
  add_executable(${PROJECT_NAME}
      src/main.cpp
      src/CanonicalObjectModel/TypeNormalization/TypeMapper.cpp
      src/Connectors/MariaDB/Connector.cpp
  )

  target_include_directories(${PROJECT_NAME}
      PRIVATE
          ${PROJECT_SOURCE_DIR}/include
          ${PROJECT_SOURCE_DIR}/external/sql-parser/src
          ${MARIADB_INCLUDE_DIRS}
  )

  target_link_libraries(${PROJECT_NAME}
      PRIVATE
          sqlparser
          ${MARIADB_LIBRARIES}
  )

  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(PostgreSQLParserTest
    src/tests/postgresql_parser_test_main.cpp
    src/Connectors/PostGreSQL/Connector.cpp
)

target_include_directories(PostgreSQLParserTest
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(PostgreSQLParserTest PRIVATE -Wall -Wextra -Wpedantic)

add_executable(PostgreSQLSchemaDiffTest
    src/tests/postgresql_schema_diff_test_main.cpp
    src/Connectors/PostGreSQL/Connector.cpp
    src/Diff/SchemaDiff.cpp
)

target_include_directories(PostgreSQLSchemaDiffTest
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(PostgreSQLSchemaDiffTest PRIVATE -Wall -Wextra -Wpedantic)

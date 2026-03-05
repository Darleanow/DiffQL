#!/usr/bin/env bash
set -euo pipefail

cmake -S . -B build
cmake --build build --target PostgreSQLSchemaDiffTest -j

PG_DUMP_BIN=""
PSQL_BIN=""
CREATEDB_BIN=""
DROPDB_BIN=""

if command -v pg_dump >/dev/null 2>&1; then
  PG_DUMP_BIN="$(command -v pg_dump)"
elif [[ -x "/opt/homebrew/opt/libpq/bin/pg_dump" ]]; then
  PG_DUMP_BIN="/opt/homebrew/opt/libpq/bin/pg_dump"
elif [[ -x "/usr/local/opt/libpq/bin/pg_dump" ]]; then
  PG_DUMP_BIN="/usr/local/opt/libpq/bin/pg_dump"
elif [[ -x "/opt/homebrew/opt/postgresql@16/bin/pg_dump" ]]; then
  PG_DUMP_BIN="/opt/homebrew/opt/postgresql@16/bin/pg_dump"
elif [[ -x "/usr/local/opt/postgresql@16/bin/pg_dump" ]]; then
  PG_DUMP_BIN="/usr/local/opt/postgresql@16/bin/pg_dump"
fi

if command -v psql >/dev/null 2>&1; then
  PSQL_BIN="$(command -v psql)"
elif [[ -x "/opt/homebrew/opt/libpq/bin/psql" ]]; then
  PSQL_BIN="/opt/homebrew/opt/libpq/bin/psql"
elif [[ -x "/usr/local/opt/libpq/bin/psql" ]]; then
  PSQL_BIN="/usr/local/opt/libpq/bin/psql"
fi

if command -v createdb >/dev/null 2>&1; then
  CREATEDB_BIN="$(command -v createdb)"
elif [[ -x "/opt/homebrew/opt/libpq/bin/createdb" ]]; then
  CREATEDB_BIN="/opt/homebrew/opt/libpq/bin/createdb"
elif [[ -x "/usr/local/opt/libpq/bin/createdb" ]]; then
  CREATEDB_BIN="/usr/local/opt/libpq/bin/createdb"
fi

if command -v dropdb >/dev/null 2>&1; then
  DROPDB_BIN="$(command -v dropdb)"
elif [[ -x "/opt/homebrew/opt/libpq/bin/dropdb" ]]; then
  DROPDB_BIN="/opt/homebrew/opt/libpq/bin/dropdb"
elif [[ -x "/usr/local/opt/libpq/bin/dropdb" ]]; then
  DROPDB_BIN="/usr/local/opt/libpq/bin/dropdb"
fi

if [[ -z "$PG_DUMP_BIN" || -z "$PSQL_BIN" || -z "$CREATEDB_BIN" || -z "$DROPDB_BIN" ]]; then
  echo "outils PostgreSQL introuvables (pg_dump/psql/createdb/dropdb)."
  echo "Sur macOS, installe le client avec: brew install libpq"
  echo "Puis ajoute au PATH (Intel): export PATH=\"/usr/local/opt/libpq/bin:\$PATH\""
  echo "Ou (Apple Silicon): export PATH=\"/opt/homebrew/opt/libpq/bin:\$PATH\""
  exit 1
fi

PATH="$(dirname "$PG_DUMP_BIN"):$PATH" \
DIFFQL_PG_DUMP_BIN="$PG_DUMP_BIN" \
DIFFQL_PSQL_BIN="$PSQL_BIN" \
DIFFQL_CREATEDB_BIN="$CREATEDB_BIN" \
DIFFQL_DROPDB_BIN="$DROPDB_BIN" \
./build/PostgreSQLSchemaDiffTest

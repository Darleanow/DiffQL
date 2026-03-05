#!/usr/bin/env bash
set -euo pipefail

cmake -S . -B build
cmake --build build --target PostgreSQLParserTest -j

PG_DUMP_BIN=""

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

if [[ -z "$PG_DUMP_BIN" ]]; then
  echo "pg_dump introuvable."
  echo "Sur macOS, installe le client avec: brew install libpq"
  echo "Puis ajoute au PATH (Intel): export PATH=\"/usr/local/opt/libpq/bin:\$PATH\""
  echo "Ou (Apple Silicon): export PATH=\"/opt/homebrew/opt/libpq/bin:\$PATH\""
  exit 1
fi

PATH="$(dirname "$PG_DUMP_BIN"):$PATH" ./build/PostgreSQLParserTest

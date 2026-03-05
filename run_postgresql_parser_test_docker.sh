#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
CONTAINER_NAME="diffql-postgresql-parser-test"
PORT="55432"
PG_USER="postgres"
PG_PASSWORD="postgres"
PG_DB="nation"
SQL_FILE="$ROOT_DIR/SampleDB/PostGreSQL/nation.sql"

if ! command -v docker >/dev/null 2>&1; then
  echo "docker introuvable"
  exit 1
fi

if ! docker info >/dev/null 2>&1; then
  echo "docker daemon non disponible"
  exit 1
fi

if [[ ! -f "$SQL_FILE" ]]; then
  echo "fichier SQL introuvable: $SQL_FILE"
  exit 1
fi

if docker ps -a --format '{{.Names}}' | grep -qx "$CONTAINER_NAME"; then
  docker rm -f "$CONTAINER_NAME" >/dev/null 2>&1 || true
fi

docker run -d \
  --name "$CONTAINER_NAME" \
  -e POSTGRES_USER="$PG_USER" \
  -e POSTGRES_PASSWORD="$PG_PASSWORD" \
  -e POSTGRES_DB="$PG_DB" \
  -p "$PORT:5432" \
  postgres:16 >/dev/null

cleanup() {
  docker rm -f "$CONTAINER_NAME" >/dev/null 2>&1 || true
}
trap cleanup EXIT

for _ in $(seq 1 40); do
  if docker exec "$CONTAINER_NAME" pg_isready -U "$PG_USER" -d "$PG_DB" >/dev/null 2>&1; then
    break
  fi
  sleep 1
done

cat "$SQL_FILE" | docker exec -i "$CONTAINER_NAME" psql -v ON_ERROR_STOP=1 -U "$PG_USER" -d "$PG_DB" >/dev/null

DIFFQL_PG_HOST=localhost \
DIFFQL_PG_PORT="$PORT" \
DIFFQL_PG_USER="$PG_USER" \
DIFFQL_PG_PASSWORD="$PG_PASSWORD" \
DIFFQL_PG_DB="$PG_DB" \
"$ROOT_DIR/run_postgresql_parser_test.sh"

#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
CONTAINER_NAME="diffql-postgresql-schema-diff-test"
PORT="55433"
PG_USER="postgres"
PG_PASSWORD="postgres"
BASE_DB="nation_v1"
TARGET_DB="nation_v2"
SQL_V1="$ROOT_DIR/SampleDB/PostGreSQL/nation_v1.sql"
SQL_V2="$ROOT_DIR/SampleDB/PostGreSQL/nation_v2.sql"

if ! command -v docker >/dev/null 2>&1; then
  echo "docker introuvable"
  exit 1
fi

if ! docker info >/dev/null 2>&1; then
  echo "docker daemon non disponible"
  exit 1
fi

if [[ ! -f "$SQL_V1" || ! -f "$SQL_V2" ]]; then
  echo "fichiers SQL introuvables"
  exit 1
fi

if docker ps -a --format '{{.Names}}' | grep -qx "$CONTAINER_NAME"; then
  docker rm -f "$CONTAINER_NAME" >/dev/null 2>&1 || true
fi

docker run -d \
  --name "$CONTAINER_NAME" \
  -e POSTGRES_USER="$PG_USER" \
  -e POSTGRES_PASSWORD="$PG_PASSWORD" \
  -e POSTGRES_DB="postgres" \
  -p "$PORT:5432" \
  postgres:16 >/dev/null

cleanup() {
  docker rm -f "$CONTAINER_NAME" >/dev/null 2>&1 || true
}
trap cleanup EXIT

for _ in $(seq 1 40); do
  if docker exec "$CONTAINER_NAME" pg_isready -U "$PG_USER" -d postgres >/dev/null 2>&1; then
    break
  fi
  sleep 1
done

docker exec "$CONTAINER_NAME" psql -v ON_ERROR_STOP=1 -U "$PG_USER" -d postgres -c "DROP DATABASE IF EXISTS $BASE_DB;" >/dev/null
docker exec "$CONTAINER_NAME" psql -v ON_ERROR_STOP=1 -U "$PG_USER" -d postgres -c "DROP DATABASE IF EXISTS $TARGET_DB;" >/dev/null
docker exec "$CONTAINER_NAME" psql -v ON_ERROR_STOP=1 -U "$PG_USER" -d postgres -c "CREATE DATABASE $BASE_DB;" >/dev/null
docker exec "$CONTAINER_NAME" psql -v ON_ERROR_STOP=1 -U "$PG_USER" -d postgres -c "CREATE DATABASE $TARGET_DB;" >/dev/null

cat "$SQL_V1" | docker exec -i "$CONTAINER_NAME" psql -v ON_ERROR_STOP=1 -U "$PG_USER" -d "$BASE_DB" >/dev/null
cat "$SQL_V2" | docker exec -i "$CONTAINER_NAME" psql -v ON_ERROR_STOP=1 -U "$PG_USER" -d "$TARGET_DB" >/dev/null

OUTPUT=$(DIFFQL_PG_HOST=localhost \
DIFFQL_PG_PORT="$PORT" \
DIFFQL_PG_USER="$PG_USER" \
DIFFQL_PG_PASSWORD="$PG_PASSWORD" \
DIFFQL_PG_BASE_DB="$BASE_DB" \
DIFFQL_PG_TARGET_DB="$TARGET_DB" \
"$ROOT_DIR/run_postgresql_schema_diff_test.sh")

echo "$OUTPUT"

echo "$OUTPUT" | grep -Fq "public.countries.name -> country_name"
echo "$OUTPUT" | grep -Fq "[RISK]"
echo "$OUTPUT" | grep -Fq "Modified CHECK: 1"
echo "$OUTPUT" | grep -Fq "Added CHECK: 1"
echo "$OUTPUT" | grep -Fq "Removed CHECK: 1"
echo "$OUTPUT" | grep -Fq "DROP TABLE public.country_languages"
echo "$OUTPUT" | grep -Fq "DROP COLUMN public.countries.national_day"

echo "validation OK (rename/check/type-warning/drop-warning)"

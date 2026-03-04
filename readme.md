# DiffQL

Database diff project (hackathon).

## Installation

### Prereqs

```bash
sudo apt install pkg-config libmariadb-dev # brew install pkg-config mariadb-connector-c
```

```bash
# Build sql-parser
cd external/sql-parser
make
cd ..
```
### Build

```bash
mkdir -p build && cd build
cmake ..
make
./DiffQL -h
```

## Limitations

For the parser:
[Hyrise SQL-Parser](https://github.com/hyrise/sql-parser/blob/main/docs/known-limitations.md)

For the diff engine:
[TODO]

## Authors

- Jory Grzeszczak
- Damien Nithard
- Aly Haidara
- Enzo Hugonnier

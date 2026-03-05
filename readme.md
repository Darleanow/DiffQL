# DiffQL

Database diff project (hackathon).

## Installation

### Prereqs

```bash
git clone git@github.com:Darleanow/DiffQL.git 
```

```bash
sudo apt install pkg-config libmariadb-dev # brew install pkg-config mariadb-connector-c
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
We support mostly DDL, for the rest, we need to extend the antlr4 grammar.
Due to time constraints, this won't change.

For the diff engine:
[TODO]

## Authors

- Jory Grzeszczak
- Damien Nithard
- Aly Haidara
- Enzo Hugonnier

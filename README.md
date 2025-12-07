# Sokoban

## Installation

```shell
git clone https://github.com/pbing/sokoban2.git
cd sokoban2
mkdir build
cmake -G Ninja -B build
cmake --build build
```

## Play

Levels are defined in XSB format. Every level must be separated with
**one blank line** (no white spaces).

Valid levels are from 1...50.

For help type
```shell
./build/src/sokoban
```

For playing level 1 type
```shell
./build/src/sokoban 1
```

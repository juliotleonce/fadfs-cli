# fadfs-cli

> [!CAUTION]
> **Project Status: Suspended (Paused)**

## Overview
`fadfs-cli` is a REPL (Read-Eval-Print Loop) implementation for [fadfs-libcore](https://github.com/juliotleonce/fadfs-libcore). It provides a command-line interface to interact with `fadfs` file system images, allowing users to perform operations like listing directories, viewing file statistics, and reading the superblock.

## Project Status
Like its core library, this project is **suspended**. The reasons for this suspension are the same as those affecting the core library:
1. **Persistent Data Corruption**
2. **Flawed Error Handling Design**

A detailed explanation of these issues can be found in the [fadfs-libcore README](https://github.com/juliotleonce/fadfs-libcore#why-this-project-is-suspended).

## Features
- **Interactive REPL:** A simple shell-like interface for executing commands.
- **Command Support:**
  - `ls <path>`: List directory contents.
  - `stat <path>`: Display file or directory metadata.
  - `sb`: Read and display superblock information.
  - `test <message>`: Simple echo command for testing.

## Getting Started
### Prerequisites
- [fadfs-libcore](https://github.com/juliotleonce/fadfs-libcore) installed or available as a dependency.
- CMake
- A C compiler (GCC/Clang)

### Build
```bash
mkdir build && cd build
cmake ..
make
```

### Usage
Run the executable with a `fadfs` disk image:
```bash
./fadfs_cli test.fadisk
```

## Future Plans
This project's future is tied to [fadfs-libcore](https://github.com/juliotleonce/fadfs-libcore). If the core library is rewritten (e.g., in Rust or C++), a corresponding CLI tool may be developed.

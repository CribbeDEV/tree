# tree

A minimal clone of the Unix `tree` command written in C. It recursively lists
the contents of a directory as an indented tree, with directories highlighted
in bold blue.

```
.
├── CMakeLists.txt
├── README.md
├── build
│   ├── ...
└── tree.c
```

## Requirements

- A C99 compiler (GCC or Clang)
- CMake 3.10 or newer
- A POSIX system (Linux, macOS, BSD) — uses `scandir` and `dirent.h`

## Building

```sh
cmake -S . -B build
cmake --build build
```

The binary is written to `build/tree`.

To install it (defaults to `/usr/local/bin`):

```sh
sudo cmake --install build
```

## Usage

```sh
./build/tree            # list the current directory
./build/tree /some/path # list a specific directory
```

Entries are sorted alphabetically. The program exits with status `1` if the
top-level directory cannot be opened.

## Notes

- Directory detection relies on `d_type`, which some filesystems report as
  `DT_UNKNOWN`; on those, directories are shown as plain files and not descended into.
- Hidden files (dotfiles) are included in the output.

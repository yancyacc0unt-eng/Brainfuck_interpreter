# Brainfuck Interpreter

A completed, lightweight Brainfuck interpreter written in C++.

## Overview

The interpreter reads a Brainfuck source file, converts its instructions into tokens, and executes them on a tape-based virtual machine. It supports all eight standard Brainfuck commands:

- `+` increments the current cell
- `-` decrements the current cell
- `>` moves the pointer right
- `<` moves the pointer left
- `.` outputs the current cell as a character
- `,` reads one input character into the current cell
- `[` jumps forward to the matching `]` when the current cell is zero
- `]` jumps back to the matching `[` when the current cell is not zero

## Project Files

- `main.cpp` contains the parser, interpreter, and command-line entry point
- `test.bf` is a sample program that prints a "Hello World!"-style message

## Build

Compile from the project directory with a C++ compiler:

```bash
g++ main.cpp -o brainfuck
```

On Windows with MinGW or MSYS2:

```powershell
g++ main.cpp -o brainfuck.exe
```

## Run

Pass the path to a Brainfuck source file as the first argument. For example, on Linux or macOS:

```bash
./brainfuck test.bf
```

On Windows:

```powershell
.\brainfuck.exe .\test.bf
```

The source file can be any Brainfuck program; replace `test.bf` with its path.

## Example

The included `test.bf` file prints a classic "Hello World!"-style message:

```text
++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
```

## Implementation

- The parser stores instructions in a linked list of tokens.
- Matching loop tokens hold references to each other for efficient jumps.
- The interpreter uses a fixed-size array of 65,536 bytes as its tape.
- Function arrays dispatch parsing and execution operations without a large switch statement.
- Unmatched loop brackets and file-open failures are reported as errors.

## Notes

- The tape pointer starts at position zero and uses an unsigned 16-bit index.
- Cell values use 8-bit unsigned integers.
- Input is read from standard input (`std::cin`).
- Output is written to standard output (`std::cout`).

## License

This project is provided as a simple educational example and is free to use and modify.

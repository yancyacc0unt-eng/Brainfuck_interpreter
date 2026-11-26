# Brainfuck Interpreter

A simple Brainfuck interpreter written in C++.

## Overview

This project reads a Brainfuck source file, converts the instructions into tokens, and executes them with a tape-based virtual machine. It supports the standard Brainfuck commands:

- `+` increments the current cell
- `-` decrements the current cell
- `>` moves the pointer right
- `<` moves the pointer left
- `.` outputs the current cell as a character
- `,` reads one input character into the current cell
- `[` jumps forward to the matching `]` if the current cell is zero
- `]` jumps back to the matching `[` if the current cell is not zero

## Project Files

- `main.cpp` contains the parser and interpreter implementation
- `test.bf` contains a sample Brainfuck program

## Build

From the project directory, compile on Linux or macOS with:

```bash
g++ main.cpp -o brainfuck
```

On Windows, MinGW or MSYS2 can use the same command. If you want an `.exe` filename, run:

```powershell
g++ main.cpp -o brainfuck.exe
```

## Run

On Linux or macOS:

```bash
./brainfuck
```

On Windows:

```powershell
.\brainfuck.exe
```

The program currently opens `test.bf` in the project directory. Command-line file paths are not yet used.

## Example

The included `test.bf` file prints a classic "Hello World!"-style message:

```text
++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
```

## Implementation

- The parser stores instructions in a linked list of `Token` structures.
- Each token keeps references to the matching opening or closing loop token.
- The interpreter uses a fixed-size array of 65,536 bytes as its tape.
- Instruction execution is dispatched through an array of functions instead of a large switch statement.
- Unmatched loop brackets are reported as errors.
- Characters that are not Brainfuck instructions are ignored.

## Notes

- The tape pointer starts at position zero.
- Cell values use 8-bit unsigned integers.
- Input is read from standard input (`std::cin`).
- Output is written to standard output (`std::cout`).

## License

This project is provided as a simple educational example and is free to use and modify.

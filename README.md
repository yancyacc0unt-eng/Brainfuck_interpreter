# Brainfuck Interpreter

A simple Brainfuck interpreter written in C++.

## Overview

This project reads a Brainfuck source file, tokenizes the instructions, and executes them using a tape-based virtual machine. It supports the standard Brainfuck commands:

- `+` increment the current cell
- `-` decrement the current cell
- `>` move the pointer right
- `<` move the pointer left
- `.` output the current cell as a character
- `,` read one input character into the current cell
- `[` jump forward to the matching `]` if the current cell is zero
- `]` jump back to the matching `[` if the current cell is non-zero

## Project Files

- `main.cpp` - interpreter implementation
- `test.bf` - sample Brainfuck program

## Build

From the project directory, compile with:

```bash
g++ main.cpp -o brainfuck
```

On Windows, you can also use MinGW or MSYS2 with the same command.

## Run

```bash
./brainfuck test.bf
```

Or on Windows:

```powershell
brainfuck.exe test.bf
```

The program expects the path to a Brainfuck source file as its first argument.

## Example

The included `test.bf` file prints a classic "Hello World!"-style message:

```text
++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
```

## Notes

- The interpreter uses a fixed-size tape of 65536 bytes.
- Input is read from standard input (`std::cin`).
- Output is written to standard output (`std::cout`).
- Unrecognized characters are ignored.

## License

This project is provided as a simple educational example and is free to use and modify.

# Sudoku Solver (C++)

A graphical Sudoku solver written in C++ that allows users to input a custom Sudoku puzzle and solve it using a backtracking algorithm. The application provides both an instant solve mode and an animated visualization mode that demonstrates the backtracking process step by step.

This project focuses on algorithm visualization, recursion, and building an interactive GUI-based application in modern C++.


## Overview

Users can manually enter a partially filled Sudoku puzzle and choose how the solution is computed:

- Animated backtracking solve for educational visualization
- Instant solve without animation for immediate results

The solver works on standard 9×9 Sudoku boards and enforces all Sudoku constraints.


## Features

- Graphical user interface
- Manual board input by the user
- Animated visualization of the backtracking algorithm
- Instant solve option without animation
- Keyboard-based controls
- Clear/reset board functionality
- Solves valid 9×9 Sudoku puzzles


## Controls

| Key | Action |
|---|---|
| `A` | Solve using animated backtracking |
| `S` | Solve instantly (no animation) |
| `C` | Clear and reset the board |

Users can click on cells and enter numbers to define a custom Sudoku puzzle before solving.


## Algorithm

The solver uses a recursive backtracking algorithm:

1. Find the next empty cell
2. Try numbers from 1 to 9
3. Check validity against:
   - Row constraints
   - Column constraints
   - 3×3 subgrid constraints
4. Place a valid number and continue recursively
5. Backtrack if no valid number can be placed

In animated mode, each placement and backtracking step is rendered visually, allowing users to observe how the algorithm explores and corrects choices.


## Building the Project

### Requirements

- C++ compiler supporting C++17 or later
- CMake 3.12 or higher

### Build Instructions

```bash
cmake -S . -B build
cmake --build build
```

### Run

```bash
./build/SudokuSolver
```

## Purpose
- This project was built to:
- Practice recursive algorithms and backtracking
- Visualize algorithmic decision-making
- Develop a GUI-based application in C++
- Demonstrate clean project structure and CMake usage
- It is suitable as a learning tool or demonstration project

## License
This project is open-source and available under the MIT License.
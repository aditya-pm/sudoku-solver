#pragma once

#include <vector>

#include "board.h"

struct Step {
    int row, col;
    int num;
    bool backtrack;
};

// highlight data for ONE frame
extern int highlight_row;
extern int highlight_col;
extern bool highlight_backtrack;

bool sudoku_solve();
void sudoku_solve_animation_create();  // create vector of individual step information
void sudoku_solve_animation_play();    // iterates through vector of steps and display each step
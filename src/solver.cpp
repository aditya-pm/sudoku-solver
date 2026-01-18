#include "solver.h"

std::vector<Step> steps;
int animation_index = 0;

// highlight (one-frame flash)
int highlight_row = -1;
int highlight_col = -1;
bool highlight_backtrack = false;

double last_step_time = 0;
double step_delay = 0.02;  // adjust animation speed

bool is_valid(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (cell_values[row][i] == num) return false;
        if (cell_values[i][col] == num) return false;
    }

    int br = row - (row % 3);
    int bc = col - (col % 3);

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (cell_values[br + r][bc + c] == num)
                return false;

    return true;
}

bool sudoku_solve() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (cell_values[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(row, col, num)) {
                        // forward move
                        cell_values[row][col] = num;
                        // program writes numbers in green, user writes in white (set in enter_digit())
                        board_font_colors[row][col] = GREEN;

                        if (sudoku_solve())
                            return true;

                        // backward move
                        cell_values[row][col] = 0;
                    }
                }
                return false;  // dead end → backtrack
            }
        }
    }
    return true;  // solved
}

bool sudoku_solve_steps() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (cell_values[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(row, col, num)) {
                        // forward move
                        cell_values[row][col] = num;
                        // program writes numbers in green, user writes in white (set in enter_digit())
                        board_font_colors[row][col] = GREEN;
                        steps.push_back({row, col, num, false});

                        if (sudoku_solve_steps())
                            return true;

                        // backward move
                        steps.push_back({row, col, 0, true});
                        cell_values[row][col] = 0;
                    }
                }
                return false;  // dead end → backtrack
            }
        }
    }
    return true;  // solved
}

void sudoku_solve_animation_create() {
    animation_index = 0;
    steps.clear();  // remove any prexisting steps

    sudoku_solve_steps();

    // reset board to empty so animation can fill it
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (!is_prefilled[r][c]) {
                cell_values[r][c] = 0;
            }
        }
    }
}

void sudoku_solve_animation_play() {
    // clear last frame's highlight
    highlight_row = -1;
    highlight_col = -1;

    if (animation_index >= steps.size())
        return;

    if (GetTime() - last_step_time < step_delay)
        return;

    last_step_time = GetTime();

    Step& s = steps[animation_index];

    // update board value
    cell_values[s.row][s.col] = s.num;

    // set highlight for THIS frame only
    highlight_row = s.row;
    highlight_col = s.col;
    highlight_backtrack = s.backtrack;

    animation_index++;
}

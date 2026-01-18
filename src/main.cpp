#include "solver.h"

int main() {
    InitWindow(810, 810, "Sudoku Solver");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        draw_title();
        select_cell();
        highlight_hovered_cell();
        enter_digit();
        draw_board();

        if (IsKeyPressed(KEY_A)) sudoku_solve_animation_create();
        if (IsKeyPressed(KEY_S)) sudoku_solve();
        if (IsKeyPressed(KEY_C)) clear_board();
        sudoku_solve_animation_play();

        EndDrawing();
    }
    return 0;
}

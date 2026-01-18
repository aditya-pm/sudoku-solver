#include "raylib.h"

#define WIDTH 1200
#define HEIGHT 800

int main() {
    InitWindow(WIDTH, HEIGHT, "Sudoku Solver");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}
#include "board.h"

#include "solver.h"

std::array<std::array<Rectangle, 9>, 9> board;
std::array<std::array<int, 9>, 9> cell_values = {};
std::array<std::array<Color, 9>, 9> board_font_colors = {};
std::array<std::array<bool, 9>, 9> is_prefilled = {};

// selected cell's row/col
int selected_row = -1;
int selected_col = -1;

void draw_title() {
    DrawText("Sudoku Solver", 150, 50, 70, WHITE);
    DrawText("PRESS A to solve (with animation)", 150, 690, 25, WHITE);
    DrawText("PRESS S to solve (no animation)", 150, 730, 25, WHITE);
    DrawText("PRESS C to clear board", 150, 770, 25, WHITE);
}

void clear_board() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cell_values[row][col] = 0;
        }
    }
}

void draw_board() {
    float bold_line_thickness = 3.0f;
    float regular_line_thickness = 0.5f;

    // outer grid
    DrawRectangleLinesEx(
        Rectangle{board_offset, board_offset, cell_size * 9, cell_size * 9},
        bold_line_thickness, WHITE);

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // bold vertical line
            if (col % 3 == 0 && col != 0) {
                Vector2 start_pos = {board_offset + cell_size * col, board_offset};
                Vector2 end_pos = {board_offset + cell_size * col, board_offset + cell_size * 9};
                DrawLineEx(start_pos, end_pos, bold_line_thickness, WHITE);
            }

            // bold horizontal line
            if (row % 3 == 0 && row != 0) {
                Vector2 start_pos = {board_offset, board_offset + cell_size * row};
                Vector2 end_pos = {board_offset + cell_size * 9, board_offset + cell_size * row};
                DrawLineEx(start_pos, end_pos, bold_line_thickness, WHITE);
            }

            // regular cell
            Rectangle cell = {(float)board_offset + col * cell_size,
                              (float)board_offset + row * cell_size,
                              (float)cell_size, (float)cell_size};
            board[row][col] = cell;
            DrawRectangleLinesEx(cell, regular_line_thickness, WHITE);

            // write number
            int value = cell_values[row][col];
            if (value != 0) {
                int textWidth = MeasureText(TextFormat("%d", value), font_size);
                float x_center = cell.x + (cell_size - textWidth) / 2;
                float y_center = cell.y + (cell_size - font_size) / 2;
                DrawText(TextFormat("%d", value), x_center, y_center, font_size, board_font_colors[row][col]);
            }

            // TEMPORARY animation highlight (one frame only)
            if (row == highlight_row && col == highlight_col) {
                Color flash = highlight_backtrack ? RED : GREEN;
                DrawRectangle(cell.x, cell.y, cell_size, cell_size, Fade(flash, 0.5f));
            }
        }
    }
}

void highlight_hovered_cell() {
    Vector2 mouse = GetMousePosition();

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            Rectangle cell = board[y][x];
            if (CheckCollisionPointRec(mouse, cell)) {
                // row rect (inset equally on left/right/top/bottom)
                Rectangle rowRect = {
                    board_offset + effectiveInset,
                    board_offset + y * cell_size + effectiveInset,
                    cell_size * 9 - 2.0f * effectiveInset,
                    cell_size - 2.0f * effectiveInset};

                // col rec
                Rectangle colRect = {
                    board_offset + x * cell_size + effectiveInset,
                    board_offset + effectiveInset,
                    cell_size - 2.0f * effectiveInset,
                    cell_size * 9 - 2.0f * effectiveInset};

                // 3x3 box rect
                int box_first_row = y - (y % 3);
                int box_first_col = x - (x % 3);
                Rectangle boxRect = {
                    board_offset + (box_first_col * cell_size) + effectiveInset,
                    board_offset + (box_first_row * cell_size) + effectiveInset,
                    cell_size * 3 - 2.0f * effectiveInset,
                    cell_size * 3 - 2.0f * effectiveInset,
                };

                DrawRectangleRounded(rowRect, roundness, segments, rowColBoxFill);
                DrawRectangleRounded(colRect, roundness, segments, rowColBoxFill);
                DrawRectangleRounded(boxRect, 0.1f, segments, rowColBoxFill);

                DrawRectangleRoundedLinesEx(rowRect, roundness, segments, outlineThickness, rowColBoxOutline);
                DrawRectangleRoundedLinesEx(colRect, roundness, segments, outlineThickness, rowColBoxOutline);
                DrawRectangleRoundedLinesEx(boxRect, 0.1f, segments, outlineThickness, rowColBoxOutline);

                return;
            }
        }
    }
}

void select_cell() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (CheckCollisionPointRec(mouse, board[row][col])) {
                    if (row == selected_row && col == selected_col) {
                        selected_row = -1;
                        selected_col = -1;
                    } else {
                        selected_row = row;
                        selected_col = col;
                    }
                }
            }
        }
    }

    if (selected_row != -1 && selected_col != -1) {
        Rectangle cell = board[selected_row][selected_col];
        Rectangle cellRect = {
            cell.x + effectiveInset, cell.y + effectiveInset,
            cell_size - 2.0f * effectiveInset, cell_size - 2.0f * effectiveInset};
        DrawRectangleRounded(cellRect, roundness, segments, selected_color_fill);
        DrawRectangleRoundedLinesEx(cellRect, roundness, segments, outlineThickness, selected_color_outline);
    }
}

void enter_digit() {
    if (selected_row != -1 && selected_col != -1) {
        int number_keys[9] = {
            KEY_ONE, KEY_TWO, KEY_THREE,
            KEY_FOUR, KEY_FIVE, KEY_SIX,
            KEY_SEVEN, KEY_EIGHT, KEY_NINE};

        for (int num = 1; num <= 9; num++) {
            if (IsKeyPressed(number_keys[num - 1])) {
                board_font_colors[selected_row][selected_col] = WHITE;
                cell_values[selected_row][selected_col] = num;
                is_prefilled[selected_row][selected_col] = true;
            }
        }

        // delete / clear
        if (IsKeyPressed(KEY_ZERO) || IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_DELETE)) {
            cell_values[selected_row][selected_col] = 0;
        }
    }
}
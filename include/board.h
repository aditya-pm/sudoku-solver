#pragma once

#include <array>

#include "raylib.h"

extern std::array<std::array<Rectangle, 9>, 9> board;
extern std::array<std::array<int, 9>, 9> cell_values;
extern std::array<std::array<Color, 9>, 9> board_font_colors;
extern std::array<std::array<bool, 9>, 9> is_prefilled;

extern int selected_row;
extern int selected_col;

inline const int font_size = 40;
inline const float board_offset = 135;
inline const float cell_size = 60;

// highlight details
inline const Color selected_color_fill = Color{0, 120, 255, 120};
inline const Color selected_color_outline = Color{0, 120, 255, 200};
inline const Color rowColBoxFill = Color{255, 200, 0, 40};
inline const Color rowColBoxOutline = Color{255, 200, 0, 200};
inline const float gap = 5.5f;
inline const float outlineThickness = 3.0f;
inline const float effectiveInset = gap + outlineThickness * 0.5f;
inline const float roundness = 0.4f;
inline const int segments = 20;

void draw_title();
void clear_board();
void draw_board();
void highlight_hovered_cell();
void select_cell();
void enter_digit();

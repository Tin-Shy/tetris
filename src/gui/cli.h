#ifndef SRC_GUI_CLI_H
#define SRC_GUI_CLI_H
#include "../brick_game/tetris.h"

#define BOARDS_BEGIN 2
#define WIDTH 10
#define HEIGHT 20

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ')

void print_next_fig_overlay(GameInfo_t* info);
void print_rect(int height, int width, int x_bias, int y_bias);
void print_stats(GameInfo_t* info);
void print_hud(GameInfo_t* info);
void print_game_overlay(GameInfo_t* info);
void display_next(GameInfo_t* info);

#endif
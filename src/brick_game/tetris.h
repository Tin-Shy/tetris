#ifndef SRC_TETRIS_TETRIS_H_
#define SRC_TETRIS_TETRIS_H_

#define EMPTY_CELL 0
#define CELL_WITH_MOVING_FIGURE 1
#define CELL_WITH_STANDING_FIGURE 2
#define ESC 27
#define ENTER_KEY 10

#define GET_USER_INPUT getch()
#define INITIAL_TIMEOUT 400

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_matrix.h"

#define WIN_INIT(time)     \
  {                        \
    initscr();             \
    setlocale(LC_ALL, ""); \
    noecho();              \
    curs_set(0);           \
    keypad(stdscr, TRUE);  \
    timeout(time);         \
  }

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

// my funcs

int get_high_score();  //
int** choose_of_next_figure();
int* start_game(GameInfo_t* info);  //
void pause_game(GameInfo_t* info);  //
void end_game(GameInfo_t* info);
int** rotate_figure(GameInfo_t* info, int** current_figure, bool flag,
                    int* place_of_current_figure);
int* move_figure(GameInfo_t* info, int direction, int* place_of_current_figure,
                 bool flag, int** current_figure);  //

// void change_plase_after_rotation(int ** current_figure, bool flag, int
// *place_of_current_figure);
int can_i_move_figure(int* place_of_current_figure, int** current_figure,
                      GameInfo_t* info, int N, int M);
int* move_figure_down(GameInfo_t* info, int* place_of_current_figure, bool flag,
                      int** current_figure);
int can_spawn_figure(GameInfo_t* info);
void free_struct(GameInfo_t* info);
void field_check(GameInfo_t* info);
void delite_line(GameInfo_t* info, int i);
void up_score(GameInfo_t* info, int cnt_lines);
void check_lvlup(GameInfo_t* info);
void check_highscore(GameInfo_t* info);
GameInfo_t updateCurrentState();
GameInfo_t* get_instance(GameInfo_t* inf);
UserAction_t key_to_action(char ch);
void update_current_and_next_figure(GameInfo_t* info);
void add_current_too_field(GameInfo_t* info);

#endif  // SRC_TETRIS_S21_TETRIS_H_

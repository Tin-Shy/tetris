#include "tetris.h"

#include "figures.h"

int** current_figure = NULL;
int* place_of_current_figure = NULL;
bool flag_was_figure_rotate = 0;

void userInput(UserAction_t action, bool hold) {
  (void)hold;
  GameInfo_t* info = get_instance(NULL);

  switch (action) {
    case Start:
      place_of_current_figure = start_game(info);
      current_figure = info->next;
      info->next = choose_of_next_figure();
      break;
    case Pause:
      pause_game(info);
      break;
    case Terminate:
      end_game(info);
      break;
    case Left:
      if (place_of_current_figure != NULL && current_figure != NULL) {
        place_of_current_figure =
            move_figure(info, -1, place_of_current_figure,
                        flag_was_figure_rotate, current_figure);
      }
      break;
    case Right:
      if (place_of_current_figure != NULL && current_figure != NULL) {
        place_of_current_figure =
            move_figure(info, 1, place_of_current_figure,
                        flag_was_figure_rotate, current_figure);
      }
      break;
    case Up:
      if (current_figure != NULL) {
        current_figure =
            rotate_figure(info, current_figure, flag_was_figure_rotate,
                          place_of_current_figure);
        flag_was_figure_rotate = !flag_was_figure_rotate;
      }
      break;
    case Down:
      int flag = 0;
      if (place_of_current_figure == &info->field[0][3]) flag = 1;
      while (place_of_current_figure != &info->field[0][3] || flag) {
        flag = 0;
        if (place_of_current_figure != NULL) {
          place_of_current_figure =
              move_figure_down(info, place_of_current_figure,
                               flag_was_figure_rotate, current_figure);
        }
      }
      break;
    case Action:
      if (place_of_current_figure != NULL && current_figure != NULL) {
        place_of_current_figure =
            move_figure_down(info, place_of_current_figure,
                             flag_was_figure_rotate, current_figure);
      }
      break;
  }
  field_check(info);
  add_current_too_field(info);
}

int* start_game(GameInfo_t* info) {
  matrix_t field_matrix;
  s21_create_matrix(20, 10, &field_matrix);

  info->field = field_matrix.matrix;
  info->next = choose_of_next_figure();
  info->score = 0;
  info->high_score = get_high_score();
  info->level = 1;
  info->speed = INITIAL_TIMEOUT;
  info->pause = 0;
  return &info->field[0][3];
}

int** choose_of_next_figure() {
  int k = rand() % 7;
  matrix_t next_matrix;
  s21_create_matrix(2, 4, &next_matrix);
  int** next = next_matrix.matrix;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      next[i][j] = figures_massive[k][i][j];
    }
  }
  return next;
}

int get_high_score() {
  FILE* f = NULL;
  int score_from_file = 0;
  if ((f = fopen("high_score.txt", "r")) != NULL) {
    fscanf(f, "%d", &score_from_file);
    fclose(f);
  }
  return score_from_file;
}

void pause_game(GameInfo_t* info) {
  info->pause = 1;
  char start;
  while (start != ESC) {
    scanf("%c", &start);
  }
  info->pause = 0;
}

void end_game(GameInfo_t* info) {
  int record = 0;
  record = get_high_score();
  if (info->score > record) {
    FILE* f = NULL;
    if ((f = fopen("high_score.txt", "w")) != NULL) {
      fprintf(f, "%d", info->score);
      fclose(f);
    }
  }
  free_struct(info);
  exit(0);
}

int** rotate_figure(GameInfo_t* info, int** current_figure, bool flag,
                    int* place_of_current_figure) {
  int N = 2, M = 4;
  if (flag) {
    N = 4;
    M = 2;
  }

  int** temp_figure = malloc(sizeof(int*) * M);
  for (int i = 0; i < M; i++) temp_figure[i] = malloc(sizeof(int) * N);

  for (int i = N - 1; i >= 0; i--) {
    for (int j = 0; j < M; j++) {
      temp_figure[j][N - 1 - i] = current_figure[i][j];
    }
  }

  if (!can_i_move_figure(place_of_current_figure, temp_figure, info, M, N)) {
    for (int i = 0; i < M; i++) {
      free(temp_figure[i]);
    }
    free(temp_figure);
    return current_figure;
  }

  for (int i = 0; i < N; i++) {
    free(current_figure[i]);
  }
  free(current_figure);

  current_figure = malloc(sizeof(int*) * M);
  for (int i = 0; i < M; i++) {
    current_figure[i] = malloc(sizeof(int) * N);
    for (int j = 0; j < N; j++) {
      current_figure[i][j] = temp_figure[i][j];
    }
  }

  for (int i = 0; i < M; i++) {
    free(temp_figure[i]);
  }
  free(temp_figure);

  return current_figure;
}

int* move_figure(GameInfo_t* info, int direction, int* place_of_current_figure,
                 bool flag, int** current_figure) {
  int N = 2, M = 4;
  if (flag) {
    N = 4;
    M = 2;
  }
  if (can_i_move_figure(place_of_current_figure + direction, current_figure,
                        info, N, M) == 1) {
    place_of_current_figure += direction;
  }

  return place_of_current_figure;
}

int* move_figure_down(GameInfo_t* info, int* place_of_current_figure, bool flag,
                      int** current_figure) {
  int N = 2, M = 4;
  if (flag) {
    N = 4;
    M = 2;
  }
  int flag_stop = 1;
  int cols = 10;
  int base_row = (place_of_current_figure - info->field[0]) / cols;
  int base_col = (place_of_current_figure - info->field[0]) % cols;
  if ((N == 2 && base_row >= 0 && base_row < 18) ||
      (N == 4 && base_row >= 0 && base_row < 17)) {
    if (can_i_move_figure(place_of_current_figure + cols, current_figure, info,
                          N, M)) {
      place_of_current_figure += cols;
      flag_stop = 0;
    }
  }
  if (flag_stop) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int row = base_row + i;
        int col = base_col + j;
        if (current_figure[i][j]) {
          info->field[row][col] = 2;
        }
      }
    }

    for (int i = 0; i < N; i++) {
      free(current_figure[i]);
    }
    free(current_figure);

    current_figure = NULL;
    place_of_current_figure = &info->field[0][3];
    update_current_and_next_figure(info);
    if (!can_spawn_figure(info)) end_game(info);
  }
  return place_of_current_figure;
}

int can_i_move_figure(int* place_of_current_figure, int** current_figure1,
                      GameInfo_t* info, int N, int M) {
  int rows = 20;
  int cols = 10;

  int base_row = (place_of_current_figure - info->field[0]) / cols;
  int base_col = (place_of_current_figure - info->field[0]) % cols;

  if (base_row >= rows || base_row < 0 || base_col >= cols || base_col < 0)
    return 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int row = base_row + i;
      int col = base_col + j;
      if (current_figure1[i][j] == 0) continue;
      if (col >= cols || col < 0 || row >= rows || row < 0) return 0;
      if (info->field[row][col] == CELL_WITH_STANDING_FIGURE) return 0;
    }
  }
  return 1;
}

int can_spawn_figure(GameInfo_t* info) {
  int flag = 1;
  int N = 2;
  int M = 4;
  int base_row = 0;
  int base_col = 3;

  for (int i = 0; i < N && flag; i++) {
    for (int j = 0; j < M; j++) {
      int row = base_row + i;
      int col = base_col + j;
      if (current_figure[i][j] && info->field[row][col] == 2) flag = 0;
      break;
    }
  }
  return flag;
}

void free_struct(GameInfo_t* info) {
  for (int i = 0; i < 20; i++) {
    free(info->field[i]);
  }
  free(info->field);
  if (info->next) {
    for (int i = 0; i < 2; i++) {
      free(info->next[i]);
    }
    free(info->next);
  }
  int N = 2;
  if (flag_was_figure_rotate) {
    N = 4;
  }

  if (current_figure) {
    for (int i = 0; i < N; i++) {
      free(current_figure[i]);
    }
    free(current_figure);
  }
}

void field_check(GameInfo_t* info) {
  int flag_is_it_row_of_2 = 1;
  int counter = 0;
  for (int i = 0; i < 20; i++) {
    flag_is_it_row_of_2 = 1;
    for (int j = 0; j < 10; j++) {
      if (info->field[i][j] != 2) {
        flag_is_it_row_of_2 = 0;
        break;
      }
    }
    if (!flag_is_it_row_of_2) continue;
    delite_line(info, i);
    counter++;
    i -= 1;
  }
  up_score(info, counter);
  check_lvlup(info);
}

void delite_line(GameInfo_t* info, int i) {
  for (int k = i; k > 0; k--) {
    for (int j = 9; j >= 0; j--) {
      info->field[k][j] = info->field[k - 1][j];
    }
  }
  i = 0;
  for (int j = 0; j < 10; j++) info->field[i][j] = 0;
}

void up_score(GameInfo_t* info, int cnt_lines) {
  switch (cnt_lines) {
    case 1:
      info->score += 100;
      break;
    case 2:
      info->score += 300;
      break;
    case 3:
      info->score += 700;
      break;
    case 4:
      info->score += 1500;
      break;
  }
  check_highscore(info);
}

void check_lvlup(GameInfo_t* info) {
  int max_score_to_lvlup = 6000;
  int lvlup_interval = 600;
  int lvlprev = info->level;

  if (info->score < max_score_to_lvlup) {
    info->level = info->score / lvlup_interval + 1;
  }

  int lvlcur = info->level;

  info->speed -= 10 * (lvlcur - lvlprev);
}

void check_highscore(GameInfo_t* info) {
  if (info->score > info->high_score) info->high_score = info->score;
}

GameInfo_t updateCurrentState() {
  GameInfo_t* info_p = get_instance(NULL);
  return *info_p;
}

GameInfo_t* get_instance(GameInfo_t* inf) {
  static GameInfo_t* game_info = {0};
  if (inf == NULL) return game_info;
  game_info = inf;
  return game_info;
}

UserAction_t key_to_action(char ch) {
  UserAction_t r;
  switch (ch) {
    case 3:  // K_UP
      r = Up;
      break;
    case 2:  // K_DOWn
      r = Down;
      break;
    case 4:  // K_LEFT
      r = Left;
      break;
    case 5:  // K_RIGHT
      r = Right;
      break;
    case ENTER_KEY:
      r = Start;
      break;
    case ESC:
      r = Terminate;
      break;
    case ' ':
      r = Pause;
      break;
    default:
      r = Action;
      break;
  }
  return r;
}

void update_current_and_next_figure(GameInfo_t* info) {
  matrix_t current_figure_matrix;
  s21_create_matrix(2, 4, &current_figure_matrix);
  current_figure = current_figure_matrix.matrix;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) current_figure[i][j] = info->next[i][j];
  }
  flag_was_figure_rotate = 0;
  info->next = choose_of_next_figure();
}

void add_current_too_field(GameInfo_t* info) {
  int N = 2, M = 4;
  if (flag_was_figure_rotate) {
    N = 4;
    M = 2;
  }

  int rows = 20;
  int cols = 10;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (info->field[i][j] == 1) info->field[i][j] = 0;
    }
  }

  int base_row = (place_of_current_figure - info->field[0]) / cols;
  int base_col = (place_of_current_figure - info->field[0]) % cols;

  for (int i = 0; i < N && current_figure != NULL; i++) {
    for (int j = 0; j < M; j++) {
      int row = base_row + i;
      int col = base_col + j;
      if (current_figure[i][j] && info->field[row][col] != 2)
        info->field[row][col] = current_figure[i][j];
    }
  }
}
#ifndef SRC_TETRIS_FIGURES_H_
#define SRC_TETRIS_FIGURES_H_

// typedef struct {
//      int first[1][4] = {1, 1, 1, 1};
//      int second[2][3] = {{1, 0 , 0}, {1, 1, 1}};
//      int third[2][3] = {{0,0,1},{1,1,1}};
//      int fourth[2][2] = {{1,1}, {1,1}};
//      int fifth[2][3] = {{0,1,1},{1,1,0}};
//      int sixth[2][3] = {{0,1,0}, {1,1,1}};
//      int seventh[2][3] = {{1,1,0},{0,1,1}};

// } figures;

static int figures_massive[7][2][4] = {
    {{0, 0, 0, 0}, {1, 1, 1, 1}}, {{1, 0, 0, 0}, {1, 1, 1, 0}},
    {{0, 0, 1, 0}, {1, 1, 1, 0}}, {{1, 1, 0, 0}, {1, 1, 0, 0}},
    {{0, 1, 1, 0}, {1, 1, 0, 0}}, {{0, 1, 0, 0}, {1, 1, 1, 0}},
    {{1, 1, 0, 0}, {0, 1, 1, 0}}};

#endif  // SRC_TETRIS_FIGURES_H_
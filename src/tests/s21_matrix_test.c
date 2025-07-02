#include "../brick_game/s21_matrix.h"

#include <check.h>

#ifdef TEST_NAME_all
#define TEST_NAME_create
#define TEST_NAME_eq
#define TEST_NAME_sum
#define TEST_NAME_sub
#define TEST_NAME_mult_n
#define TEST_NAME_mult_m
#define TEST_NAME_transpose
#define TEST_NAME_determinant
#define TEST_NAME_complements
#define TEST_NAME_inverse
#define TEST_NAME_remove
#endif

void fill_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = i + j;
    }
  }
}

void fill_matrix_double(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (A->rows != 0) {
        A->matrix[i][j] = (double)(i + j) / (double)(A->rows + A->columns);
      }
    }
  }
}

#ifdef TEST_NAME_create
START_TEST(s21_create_t1) {
  int rows = 4;
  int columns = 5;
  int f_res = CALC_OK;
  matrix_t result;

  int s21_res = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(rows, result.rows);
  ck_assert_int_eq(columns, result.columns);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_create_t2) {
  int rows = 0;
  int columns = 5;
  int f_res = CALC_INCORRECT_MATRIX;
  matrix_t result;

  int s21_res = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(f_res, s21_res);
}
END_TEST

START_TEST(s21_create_t3) {
  int rows = 5;
  int columns = 0;
  int f_res = CALC_INCORRECT_MATRIX;
  matrix_t result;

  int s21_res = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(f_res, s21_res);
}
END_TEST

START_TEST(s21_create_t4) {
  int rows = -1;
  int columns = 5;
  int f_res = CALC_INCORRECT_MATRIX;
  matrix_t result;

  int s21_res = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(f_res, s21_res);
}
END_TEST

START_TEST(s21_create_t5) {
  int rows = 5;
  int columns = -1;
  int f_res = CALC_INCORRECT_MATRIX;
  matrix_t result;

  int s21_res = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(f_res, s21_res);
}
END_TEST

START_TEST(s21_create_t6) {
  int rows = 100;
  int columns = 200;
  int f_res = CALC_OK;
  matrix_t result;

  int s21_res = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(rows, result.rows);
  ck_assert_int_eq(columns, result.columns);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&result);
}
END_TEST
#endif  // END TESTS FOR create

#ifdef TEST_NAME_eq
START_TEST(s21_eq_t1) {
  // матрицы одной размерности
  int rows = 1;
  int columns = 3;
  int f_res = SUCCESS;
  matrix_t A, B;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  // создаем одинаковые матрицы
  fill_matrix(&A);
  fill_matrix(&B);

  int s21_res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(f_res, s21_res);

  matrix_t C;
  s21_mult_number(&A, 3, &C);
  s21_remove_matrix(&A);
  s21_res = s21_eq_matrix(&C, &B);
  f_res = FAILURE;
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&C);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_t2) {
  // матрицы разной размерности
  int rows = 1;
  int columns = 3;
  int f_res = FAILURE;
  matrix_t A, B;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &B);
  // заполняем матрицы
  fill_matrix(&A);
  fill_matrix(&B);

  int s21_res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
#endif  // END TESTS FOR eq

#ifdef TEST_NAME_sum
START_TEST(s21_sum_t1) {
  int rows = 2;
  int columns = 3;
  int f_res = CALC_OK;
  matrix_t A, B, result;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  fill_matrix(&A);
  fill_matrix(&B);

  int s21_res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(f_res, s21_res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j],
                          (A.matrix[i][j] + B.matrix[i][j]));
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_t2) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  int f_res = CALC_ERROR;

  s21_create_matrix(4, 3, &A);
  s21_create_matrix(3, 4, &B);
  fill_matrix(&A);
  fill_matrix(&B);
  int s21_res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(s21_res, f_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_t3) {
  int rows = 8;
  int columns = 9;
  int f_res = CALC_OK;
  matrix_t A, B, result;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  fill_matrix_double(&A);
  fill_matrix_double(&B);

  int s21_res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(f_res, s21_res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_ldouble_eq_tol(result.matrix[i][j],
                               (A.matrix[i][j] + B.matrix[i][j]), 1e-6);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
#endif  // END TESTS FOR sum

#ifdef TEST_NAME_sub
START_TEST(s21_sub_t1) {
  int rows = 2;
  int columns = 3;
  int f_res = CALC_OK;
  matrix_t A, B, result;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  fill_matrix(&A);
  fill_matrix(&B);

  int s21_res = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(f_res, s21_res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j],
                          (A.matrix[i][j] - B.matrix[i][j]));
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_t2) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  int f_res = CALC_ERROR;

  s21_create_matrix(4, 3, &A);
  s21_create_matrix(3, 4, &B);
  fill_matrix(&A);
  fill_matrix(&B);
  int s21_res = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(s21_res, f_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_t3) {
  int rows = 8;
  int columns = 9;
  int f_res = CALC_OK;
  matrix_t A, B, result;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  fill_matrix_double(&A);
  fill_matrix_double(&B);

  int s21_res = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(f_res, s21_res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_ldouble_eq_tol(result.matrix[i][j],
                               (A.matrix[i][j] - B.matrix[i][j]), 1e-6);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
#endif  // END TESTS FOR sub

#ifdef TEST_NAME_mult_m
START_TEST(s21_mult_m_t1) {
  int rows = 2;
  int columns = 3;
  int f_res = CALC_ERROR;
  matrix_t A, B, result;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  fill_matrix(&A);
  fill_matrix(&B);

  int s21_res = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_m_t2) {
  matrix_t A;
  matrix_t B;
  matrix_t result, model;
  int f_res = CALC_OK;

  s21_create_matrix(4, 3, &A);
  s21_create_matrix(3, 4, &B);
  s21_create_matrix(4, 4, &model);
  fill_matrix(&A);
  fill_matrix(&B);
  model.matrix[0][0] = 5;
  model.matrix[0][1] = 8;
  model.matrix[0][2] = 11;
  model.matrix[0][3] = 14;
  model.matrix[1][0] = 8;
  model.matrix[1][1] = 14;
  model.matrix[1][2] = 20;
  model.matrix[1][3] = 26;
  model.matrix[2][0] = 11;
  model.matrix[2][1] = 20;
  model.matrix[2][2] = 29;
  model.matrix[2][3] = 38;
  model.matrix[3][0] = 14;
  model.matrix[3][1] = 26;
  model.matrix[3][2] = 38;
  model.matrix[3][3] = 50;
  int s21_res = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(s21_res, f_res);
  for (int i = 0; i < model.rows; i++)
    for (int j = 0; j < model.columns; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], model.matrix[i][j], 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&model);
}
END_TEST

START_TEST(s21_mult_m_t3) {
  matrix_t A;
  matrix_t B;
  matrix_t result, model;
  int f_res = CALC_OK;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(2, 3, &model);
  fill_matrix(&A);
  fill_matrix(&B);
  model.matrix[0][0] = 5;
  model.matrix[0][1] = 8;
  model.matrix[0][2] = 11;
  model.matrix[1][0] = 8;
  model.matrix[1][1] = 14;
  model.matrix[1][2] = 20;
  int s21_res = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(s21_res, f_res);
  for (int i = 0; i < model.rows; i++)
    for (int j = 0; j < model.columns; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], model.matrix[i][j], 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&model);
}
END_TEST

START_TEST(s21_mult_m_t4) {
  matrix_t A;
  matrix_t B;
  matrix_t result, model;
  int f_res = CALC_OK;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &model);
  fill_matrix_double(&A);
  fill_matrix_double(&B);
  model.matrix[0][0] = 0.2;
  model.matrix[0][1] = 0.32;
  model.matrix[1][0] = 0.32;
  model.matrix[1][1] = 0.56;
  int s21_res = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(s21_res, f_res);
  for (int i = 0; i < model.rows; i++)
    for (int j = 0; j < model.columns; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], model.matrix[i][j], 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&model);
}
END_TEST
#endif  // END TESTS FOR mult_m

#ifdef TEST_NAME_mult_n
START_TEST(s21_mult_n_t1) {
  int rows = 2;
  int columns = 3;
  double numb = 5;
  int f_res = CALC_OK;
  matrix_t A, result;

  s21_create_matrix(rows, columns, &A);
  fill_matrix(&A);

  int s21_res = s21_mult_number(&A, numb, &result);
  ck_assert_int_eq(f_res, s21_res);
  for (int i = 0; i < result.rows; i++)
    for (int j = 0; j < result.columns; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], A.matrix[i][j] * 5.0, 1e-6);

  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_mult_n_t2) {
  int rows = 2;
  int columns = 3;
  double numb = NAN;
  int f_res = CALC_ERROR;
  matrix_t A, result;

  s21_create_matrix(rows, columns, &A);
  fill_matrix(&A);

  int s21_res = s21_mult_number(&A, numb, &result);
  ck_assert_int_eq(f_res, s21_res);
  numb = 1.0 / 0.0;
  s21_res = s21_mult_number(&A, numb, &result);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST
#endif  // END TESTS FOR mult_n

#ifdef TEST_NAME_determinant

START_TEST(s21_determinant_t1) {
  matrix_t A;
  double result = 0.0;
  int f_res = CALC_OK;

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 11;
  A.matrix[0][3] = 14;
  A.matrix[1][0] = 8;
  A.matrix[1][1] = 14;
  A.matrix[1][2] = 20;
  A.matrix[1][3] = 26;
  A.matrix[2][0] = 11;
  A.matrix[2][1] = 20;
  A.matrix[2][2] = 29;
  A.matrix[2][3] = 38;
  A.matrix[3][0] = 14;
  A.matrix[3][1] = 26;
  A.matrix[3][2] = 38;
  A.matrix[3][3] = 50;
  int s21_res = s21_determinant(&A, &result);
  ck_assert_double_eq(result, 0.0);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_t2) {
  matrix_t A;
  int f_res = CALC_OK;
  double deter = 0.0;

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 1;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix[2][3] = 3;
  A.matrix[3][0] = 3;
  A.matrix[3][1] = 7;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 4;
  int s21_res = s21_determinant(&A, &deter);
  ck_assert_int_eq(f_res, s21_res);
  ck_assert_int_eq(deter, -120);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_t3) {
  matrix_t A;
  int f_res = CALC_OK;
  double res = 0.0;

  s21_create_matrix(5, 5, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[0][4] = 5;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 1;
  A.matrix[1][4] = 8;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix[2][3] = 3;
  A.matrix[2][4] = 7;
  A.matrix[3][0] = 3;
  A.matrix[3][1] = 7;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 4;
  A.matrix[3][4] = 9;
  A.matrix[4][0] = 4;
  A.matrix[4][1] = 5;
  A.matrix[4][2] = 7;
  A.matrix[4][3] = 13;
  A.matrix[4][4] = 11;

  int s21_res = s21_determinant(&A, &res);
  ck_assert_int_eq(f_res, s21_res);
  ck_assert_int_eq(res, -504);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_t4) {
  matrix_t A;
  int f_res = CALC_OK;
  double res = 0.0;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int s21_res = s21_determinant(&A, &res);
  ck_assert_int_eq(f_res, s21_res);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_t5) {
  matrix_t A;
  int f_res = CALC_OK;
  double res = 0.0;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 5;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 8;
  int s21_res = s21_determinant(&A, &res);
  ck_assert_int_eq(f_res, s21_res);
  ck_assert_int_eq(res, -3);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_t6) {
  matrix_t A;
  int f_res = CALC_OK;
  double res = 0.0;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 4;

  int s21_res = s21_determinant(&A, &res);
  ck_assert_int_eq(f_res, s21_res);
  ck_assert_int_eq(res, 4);
  s21_remove_matrix(&A);
}
END_TEST
#endif  // END TESTS FOR determinant

#ifdef TEST_NAME_transpose
START_TEST(s21_transpose_t) {
  matrix_t A, result, model;
  int f_res = CALC_OK;

  s21_create_matrix(5, 2, &A);
  fill_matrix(&A);

  int s21_res = s21_transpose(&A, &result);
  ck_assert_int_eq(f_res, s21_res);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 5);

  s21_create_matrix(2, 5, &model);
  model.matrix[0][0] = 0;
  model.matrix[0][1] = 1;
  model.matrix[0][2] = 2;
  model.matrix[0][3] = 3;
  model.matrix[0][4] = 4;
  model.matrix[1][0] = 1;
  model.matrix[1][1] = 2;
  model.matrix[1][2] = 3;
  model.matrix[1][3] = 4;
  model.matrix[1][4] = 5;

  for (int i = 0; i < model.rows; i++) {
    for (int j = 0; j < model.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], model.matrix[i][j]);
    }
  }
  s21_remove_matrix(&model);
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
}
END_TEST
#endif  // END TESTS FOR transpose

#ifdef TEST_NAME_inverse
START_TEST(s21_inverse_t1) {
  int rows = 2;
  int columns = 5;
  int f_res = CALC_ERROR;
  matrix_t A, result;

  s21_create_matrix(rows, columns, &A);

  int s21_res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_t2) {
  int f_res = CALC_OK;
  matrix_t A, result;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;

  int s21_res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(f_res, s21_res);
  ck_assert_double_eq_tol(0.5, result.matrix[0][0], 1e-6);

  s21_remove_matrix(&result);

  A.matrix[0][0] = 0.0;
  f_res = CALC_ERROR;
  s21_res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_t3) {
  matrix_t A;
  matrix_t result;
  int f_res = CALC_ERROR;

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 11;
  A.matrix[0][3] = 14;
  A.matrix[1][0] = 8;
  A.matrix[1][1] = 14;
  A.matrix[1][2] = 20;
  A.matrix[1][3] = 26;
  A.matrix[2][0] = 22;
  A.matrix[2][1] = 20;
  A.matrix[2][2] = 29;
  A.matrix[2][3] = 38;
  A.matrix[3][0] = 14;
  A.matrix[3][1] = 26;
  A.matrix[3][2] = 38;
  A.matrix[3][3] = 50;
  int s21_res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_t4) {
  matrix_t A;
  matrix_t result;
  int f_res = CALC_ERROR;

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 11;
  A.matrix[0][3] = 14;
  A.matrix[1][0] = 8;
  A.matrix[1][1] = 14;
  A.matrix[1][2] = 20;
  A.matrix[1][3] = 26;
  A.matrix[2][0] = 11;
  A.matrix[2][1] = 20;
  A.matrix[2][2] = 29;
  A.matrix[2][3] = 38;
  A.matrix[3][0] = 14;
  A.matrix[3][1] = 26;
  A.matrix[3][2] = 38;
  A.matrix[3][3] = 50;
  int s21_res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(f_res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_t5) {
  matrix_t A, model, result;
  int f_res = CALC_OK;

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &model);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 1;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix[2][3] = 3;
  A.matrix[3][0] = 3;
  A.matrix[3][1] = 7;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 4;
  int s21_res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(f_res, s21_res);
  model.matrix[0][0] = -0.125;
  model.matrix[0][1] = 23.0 / 120;
  model.matrix[0][2] = 0.325;
  model.matrix[0][3] = -1.0 / 6;
  model.matrix[1][0] = -0.125;
  model.matrix[1][1] = 7.0 / 120;
  model.matrix[1][2] = -0.075;
  model.matrix[1][3] = 1.0 / 6;
  model.matrix[2][0] = 0.125;
  model.matrix[2][1] = 0.675;
  model.matrix[2][2] = 0.275;
  model.matrix[2][3] = -0.5;
  model.matrix[3][0] = 0.25;
  model.matrix[3][1] = -7.0 / 12;
  model.matrix[3][2] = -0.25;
  model.matrix[3][3] = 1.0 / 3;
  for (int i = 0; i < model.rows; i++)
    for (int j = 0; j < model.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], model.matrix[i][j], 1e-6);
    }
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&model);
}
END_TEST
#endif  // END TESTS FOR inverse

#ifdef TEST_NAME_complements
START_TEST(s21_calc_complements_t1) {
  int rows = 2;
  int columns = 3;
  int f_res = CALC_ERROR;
  matrix_t A, result;

  s21_create_matrix(rows, columns, &A);
  fill_matrix(&A);
  int s21_res = s21_calc_complements(&A, &result);
  ck_assert_int_eq(f_res, s21_res);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_t2) {
  matrix_t A, result, model;
  int f_res = CALC_OK;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &model);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  model.matrix[0][0] = 0;
  model.matrix[0][1] = 10;
  model.matrix[0][2] = -20;
  model.matrix[1][0] = 4;
  model.matrix[1][1] = -14;
  model.matrix[1][2] = 8;
  model.matrix[2][0] = -8;
  model.matrix[2][1] = -2;
  model.matrix[2][2] = 4;
  int s21_res = s21_calc_complements(&A, &result);
  ck_assert_int_eq(f_res, s21_res);

  for (int i = 0; i < model.rows; i++)
    for (int j = 0; j < model.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], model.matrix[i][j], 1e-6);
    }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&model);
}
END_TEST
#endif  // END TESTS FOR complements

#ifdef TEST_NAME_remove
START_TEST(s21_remove_t) {
  int rows = 1;
  int columns = 3;
  matrix_t result;
  s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(0, result.rows);
  ck_assert_int_eq(0, result.columns);
}
END_TEST
#endif  // END TESTS FOR remove

Suite *s21_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_matrix");
  tc_core = tcase_create("Core");

#ifdef TEST_NAME_create
  tcase_add_test(tc_core, s21_create_t1);
  tcase_add_test(tc_core, s21_create_t2);
  tcase_add_test(tc_core, s21_create_t3);
  tcase_add_test(tc_core, s21_create_t4);
  tcase_add_test(tc_core, s21_create_t5);
  tcase_add_test(tc_core, s21_create_t6);
#endif

#ifdef TEST_NAME_eq
  tcase_add_test(tc_core, s21_eq_t1);
  tcase_add_test(tc_core, s21_eq_t2);
#endif

#ifdef TEST_NAME_sum
  tcase_add_test(tc_core, s21_sum_t1);
  tcase_add_test(tc_core, s21_sum_t2);
  tcase_add_test(tc_core, s21_sum_t3);
#endif

#ifdef TEST_NAME_sub
  tcase_add_test(tc_core, s21_sub_t1);
  tcase_add_test(tc_core, s21_sub_t2);
  tcase_add_test(tc_core, s21_sub_t3);
#endif

#ifdef TEST_NAME_mult_m
  tcase_add_test(tc_core, s21_mult_m_t1);
  tcase_add_test(tc_core, s21_mult_m_t2);
  tcase_add_test(tc_core, s21_mult_m_t3);
  tcase_add_test(tc_core, s21_mult_m_t4);
#endif

#ifdef TEST_NAME_mult_n
  tcase_add_test(tc_core, s21_mult_n_t1);
  tcase_add_test(tc_core, s21_mult_n_t2);
#endif

#ifdef TEST_NAME_determinant
  tcase_add_test(tc_core, s21_determinant_t1);
  tcase_add_test(tc_core, s21_determinant_t2);
  tcase_add_test(tc_core, s21_determinant_t3);
  tcase_add_test(tc_core, s21_determinant_t4);
  tcase_add_test(tc_core, s21_determinant_t5);
  tcase_add_test(tc_core, s21_determinant_t6);
#endif

#ifdef TEST_NAME_inverse
  tcase_add_test(tc_core, s21_inverse_t1);
  tcase_add_test(tc_core, s21_inverse_t2);
  tcase_add_test(tc_core, s21_inverse_t3);
  tcase_add_test(tc_core, s21_inverse_t4);
  tcase_add_test(tc_core, s21_inverse_t5);
#endif  // END TESTS FOR inverse

#ifdef TEST_NAME_complements
  tcase_add_test(tc_core, s21_calc_complements_t1);
  tcase_add_test(tc_core, s21_calc_complements_t2);
#endif  // END TESTS FOR complements

#ifdef TEST_NAME_transpose
  tcase_add_test(tc_core, s21_transpose_t);
#endif

#ifdef TEST_NAME_remove
  tcase_add_test(tc_core, s21_remove_t);
#endif

  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_matrix_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

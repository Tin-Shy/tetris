#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = 0;
  if (rows <= 0 || columns <= 0) {
    flag = 1;
    result->columns = 0;
    result->rows = 0;
    // result->matrix = NULL;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (int *)calloc(columns, sizeof(int));
    }
    if (result->matrix == NULL) {
      flag = 2;
    }
  }
  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->columns = 0;
  A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows) {
    flag = FAILURE;
    return flag;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if ((A->matrix[i][j] - B->matrix[i][j]) != 0) {
        flag = FAILURE;
        break;
      }
    }
  }
  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->columns != B->columns || A->rows != B->rows) {
    flag = 2;
    return flag;
  }
  if (A->columns <= 0 || B->columns <= 0 || A->rows <= 0 || B->rows <= 0) {
    flag = 1;
    return flag;
  }
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->columns != B->columns || A->rows != B->rows) {
    flag = 2;
    return flag;
  }
  if (A->columns <= 0 || B->columns <= 0 || A->rows <= 0 || B->rows <= 0) {
    flag = 1;
    return flag;
  }
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = 0;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = 1;
    return flag;
  }
  if (isnan(number) || isinf(number)) {
    flag = 2;
    return flag;
  }
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->columns != B->rows) {
    flag = 2;
    return flag;
  }
  if (A->columns <= 0 || B->columns <= 0 || A->rows <= 0 || B->rows <= 0) {
    flag = 1;
    return flag;
  }
  s21_create_matrix(A->rows, B->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = 1;
    return flag;
  }
  s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = 1;
  } else if (A->columns != A->rows) {
    flag = 2;
  } else if (A->columns == 1 && A->rows == 1) {
    result->matrix[0][0] = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor;
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        fill_minor_matrix(i, j, A, &minor);
        double minor_determinant = 0.0;
        s21_determinant(&minor, &minor_determinant);
        result->matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor_determinant;
        s21_remove_matrix(&minor);
      }
    }
  }
  return flag;
}

void fill_minor_matrix(int i_input, int j_input, matrix_t *A, matrix_t *temp) {
  int n = 0;
  for (int i = 0; i < A->rows; ++i) {
    if (i == i_input) continue;
    int m = 0;
    for (int j = 0; j < A->columns; ++j) {
      if (j == j_input) continue;
      temp->matrix[n][m] = A->matrix[i][j];
      m++;
    }
    n++;
  }
}
int s21_determinant(matrix_t *A, double *result) {
  int flag = 0;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = 1;
  } else if (A->columns != A->rows) {
    flag = 2;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    matrix_t cc;
    s21_calc_complements(A, &cc);
    for (int i = 0; i < A->columns; ++i) {
      *result = A->matrix[0][i] * cc.matrix[0][i] + (*result);
    }
    s21_remove_matrix(&cc);
  }
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->columns <= 0 || A->rows <= 0) {
    flag = 1;
  } else if (A->columns != A->rows) {
    flag = 2;
  } else {
    double temp1 = 0.0;
    s21_determinant(A, &temp1);
    if (fabs(temp1) <= EPS) {
      flag = 2;
    } else {
      if (A->rows == 1) {
        s21_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1. / A->matrix[0][0];
      } else {
        matrix_t temp, temp2;
        double new_det = 1.0 / temp1;
        flag = s21_calc_complements(A, &temp);
        flag = s21_transpose(&temp, &temp2);
        flag = s21_mult_number(&temp2, new_det, result);

        s21_remove_matrix(&temp);
        s21_remove_matrix(&temp2);
      }
    }
  }
  return flag;
}
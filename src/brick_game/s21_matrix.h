#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

#define CALC_ERROR 2
#define CALC_OK 0
#define CALC_INCORRECT_MATRIX 1

typedef struct matrix_struct {
  int **matrix;
  int rows;
  int columns;
} matrix_t;

// Все операции (кроме сравнения матриц) должны возвращать результирующий код:

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int s21_create_matrix(int rows, int columns, matrix_t *result);  //
void s21_remove_matrix(matrix_t *A);                             //

int s21_eq_matrix(matrix_t *A, matrix_t *B);  //

// Две матрицы A, B совпадают |A = B|, если совпадают их размеры и
// соответствующие элементы равны, то есть при всех i, j A(i,j) = B(i,j).
// Сравнение должно происходить вплоть до седьмого знака после запятой
// включительно.

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  //
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  //

// Суммой двух матриц A = m × n и B = m × n одинаковых размеров называется
// матрица C = m × n = A + B тех же размеров, элементы которой определяются
// равенствами C(i,j) = A(i,j) + B(i,j). Разностью двух матриц A = m × n и B = m
// × n одинаковых размеров называется матрица C = m × n = A - B тех же размеров,
// элементы которой определяются равенствами C(i,j) = A(i,j) - B(i,j).

int s21_mult_number(matrix_t *A, double number, matrix_t *result);  //
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    //

int s21_transpose(matrix_t *A, matrix_t *result);  //

int s21_calc_complements(matrix_t *A, matrix_t *result);  //

int s21_determinant(matrix_t *A, double *result);  //

int s21_inverse_matrix(matrix_t *A, matrix_t *result);  //

// my_functions
void print_matrix(matrix_t *temp);
void fill_minor_matrix(int i, int j, matrix_t *A, matrix_t *temp);

#endif

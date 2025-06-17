#pragma once

#ifndef MATRIX_MATMUL_H
#define MATRIX_MATMUL_H

// Matrix structure and constants
struct Matrix;
#define MATX_OP_FAILURE 0
#define MATX_OP_INCOMPATIBLE 1
#define MATX_OP_SUCCESS 9



// Function prototypes
Matrix* matrix_create(int _matrix_id, int _operand_id, int _rows, int _cols, int _matrix_type);
void matrix_free(Matrix* m);
double matrix_get_ushort(const Matrix* m, int row, int col);
double matrix_get_uint(const Matrix* m, int row, int col);
void matrix_set_ushort(Matrix* m, int row, int col, unsigned short int value);
void matrix_set_uint(Matrix* m, int row, int col, unsigned short int value);
unsigned int matrix_MatrixMultiply2(Matrix* _matrix1, Matrix* _matrix2, Matrix* _matrix_result);
unsigned short int generate_random_ushort(void);
unsigned short init_matrix1(Matrix* mat);
unsigned short init_matrix2(Matrix* mat);
void print_matrix(const Matrix* mat, int print_type);

#endif
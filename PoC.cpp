#include <iostream>

#include "MatMul.h"
#include "common.h"

//#include "MatrixPersistence.h"

/*
int main() {

    int mat1_row_count = 20;
    int mat1_col_count = 25;

    int mat2_row_count = 25;
    int mat2_col_count = 20;


    //int mat1_row_count = 2;
    //int mat1_col_count = 4;

    //int mat2_row_count = 4;
    //int mat2_col_count = 3;
	unsigned short matrix_id = 0;
	unsigned short operation_id = 0;

    // Create 2x3 matrix (initialized to zeros)
    Matrix* mat1 = matrix_create(matrix_id, operation_id, mat1_row_count, mat1_col_count, MATRIX_TYPE_OPERAND);
    if (!mat1) {
        std::cerr << "Matrix allocation failed!" << std::endl;
        return 1;
    }

    Matrix* mat2 = matrix_create(matrix_id, operation_id, mat2_row_count, mat2_col_count, MATRIX_TYPE_OPERAND);
    if (!mat2) {
        std::cerr << "Matrix allocation failed!" << std::endl;
        return 1;
    }

    Matrix* mat_result = matrix_create(matrix_id, operation_id, mat1_row_count, mat2_col_count, MATRIX_TYPE_RESULT);
    if (!mat_result) {
        std::cerr << "Matrix allocation failed!" << std::endl;
        return 1;
    }

    unsigned short result;

    result = init_matrix1(mat1);
    result = init_matrix2(mat2);

    // Perform matrix multiplication

    unsigned int mul_result = matrix_MatrixMultiply2(mat1, mat2, mat_result);

    // Read values
    std::cout << "Matrix Result:\n";
	print_matrix(mat_result, MATRIX_TYPE_RESULT);

    // Free memory
    matrix_free(mat1);
    matrix_free(mat2);
    matrix_free(mat_result);

    return 0;
} */
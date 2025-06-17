// MatMul1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>   // For malloc, calloc, free
#include <stdlib.h>
#include <stdexcept> // For std::out_of_range
#include "MatMul.h"
#include "common.h"

using namespace std;

// Allocates matrix memory (initialized to zero)
Matrix* matrix_create(int _matrix_id, int _operand_id, int _rows, int _cols, int _matrix_type) {
    Matrix* m = static_cast<Matrix*>(malloc(sizeof(Matrix)));
    if (!m) return nullptr;

	m->matrix_id = _matrix_id;   
    m->operand_id = _operand_id;
    m->rows = _rows;
    m->cols = _cols;

    if (_matrix_type == MATRIX_TYPE_OPERAND) {
        m->matrix_type = MATRIX_TYPE_OPERAND;
        m->ushort_data = static_cast<unsigned short int*>(calloc(_rows * _cols, sizeof(unsigned short int)));
    } 
    else if (_matrix_type == MATRIX_TYPE_RESULT) {
        m->matrix_type = MATRIX_TYPE_RESULT;
        m->uint_data = static_cast<unsigned  int*>(calloc(_rows * _cols, sizeof(unsigned  int)));
    } 
    else {
        free(m);
        return nullptr; // Invalid matrix type
	}
    
    if ( (!m->ushort_data) && ( !m->uint_data)) {
        free(m);
        return nullptr;
    }
    return m;
}

// Safely deallocates matrix memory
void matrix_free(Matrix* m) {
    if (m) {
        free(m->ushort_data);  // Free data array first
        free(m);        // Then free struct
    }
}



unsigned int matrix_MatrixMultiply2(Matrix* _matrix1, Matrix* _matrix2, Matrix* _matrix_result) {

	unsigned int result = 0;
	// check if matrices can be multiplied
    if (_matrix1->cols != _matrix2->rows) {
        result = MATX_OP_INCOMPATIBLE;
		return result;
    }
	// Initialize result matrix
	//_matrix_result = matrix_create(_matrix1->rows, _matrix2->cols);
    if (!_matrix_result) {
        result = MATX_OP_FAILURE;
		return result;
    }

    else {
		for (int row_counter = 0; row_counter < _matrix_result->rows; ++row_counter) {                // _matrix_result->rows = _matrix1->rows
			for (int col_counter = 0; col_counter < _matrix_result->cols; ++col_counter) {            // _matrix_result->cols = _matrix2->cols
				unsigned int sum = 0;
                for (int common_dim = 0; common_dim < _matrix2->rows; ++common_dim) {                   // _matrix1->cols = _matrix2->rows
                    unsigned short int a = _matrix1->ushort_data[row_counter * _matrix1->cols + common_dim];
                    unsigned short int b = _matrix2->ushort_data[common_dim * _matrix2->cols + col_counter];
                    std::cout << "Multiplying: " << a << " * " << b << std::endl; // Debug output
                    sum += a * b;
                }
                std::cout << "Sum: " << sum << std::endl; // Debug output
				_matrix_result->uint_data[row_counter * _matrix_result->cols + col_counter] = sum; // Store result
                std::cout << "Result of Row: " << row_counter << " Col: " << col_counter << " = " << _matrix_result->uint_data[row_counter * _matrix_result->cols + col_counter] << std::endl; // Debug output
            }
        }
        result = MATX_OP_SUCCESS;
	}

    return result;
}


unsigned short int generate_random_ushort(void) {
    unsigned int r1 = (unsigned int)rand();
    unsigned int r2 = (unsigned int)rand();
    return (unsigned short int)(((r1 >> 7) << 8) | (r2 >> 7));
}

//unsigned int matrixMultiply1(int** mat1, int rows1, int cols1,
//    int** mat2, int rows2, int cols2,
//    int** result) {
//    // Check if matrices can be multiplied
//    if (cols1 != rows2) {
//        // Handle incompatible dimensions: set result to zeros or leave unchanged
//        return 0;
//    }
//
//    // Initialize result matrix to zeros
//    for (int i = 0; i < rows1; ++i) {
//        for (int j = 0; j < cols2; ++j) {
//            result[i][j] = 0;
//        }
//    }
//
//    // Perform matrix multiplication
//    for (int i = 0; i < rows1; ++i) {
//        for (int j = 0; j < cols2; ++j) {
//            for (int k = 0; k < cols1; ++k) {
//                result[i][j] += mat1[i][k] * mat2[k][j];
//            }
//        }
//    }
//}

unsigned short init_matrix1(Matrix* mat) {
    //// Set values
    matrix_set_ushort(mat, 0, 0, 3);
    matrix_set_ushort(mat, 0, 1, 2);
    matrix_set_ushort(mat, 0, 2, 1);
    matrix_set_ushort(mat, 0, 3, 5);

    matrix_set_ushort(mat, 1, 0, 9);
    matrix_set_ushort(mat, 1, 1, 1);
    matrix_set_ushort(mat, 1, 2, 3);
    matrix_set_ushort(mat, 1, 3, 0);

 //   for (int i = 0; i < mat->rows; ++i) {
 //       for (int j = 0; j < mat->cols; ++j) {
	//		matrix_set(mat, i, j, generate_random_ushort()); // Initialize remaining elements to random values
 //       }
	//}

    std::cout << "Matrix 1 Initialized, Size:" << mat->rows << " x " << mat->cols << " matrix " << std::endl; // Debug output

    return (unsigned short)0;
}

unsigned short init_matrix2(Matrix* mat) {
    // Set values
    matrix_set_ushort(mat, 0, 0, 2);
    matrix_set_ushort(mat, 0, 1, 9);
    matrix_set_ushort(mat, 0, 2, 0);

    matrix_set_ushort(mat, 1, 0, 1);
    matrix_set_ushort(mat, 1, 1, 3);
    matrix_set_ushort(mat, 1, 2, 5);

    matrix_set_ushort(mat, 2, 0, 2);
    matrix_set_ushort(mat, 2, 1, 4);
    matrix_set_ushort(mat, 2, 2, 7);

    matrix_set_ushort(mat, 3, 0, 8);
    matrix_set_ushort(mat, 3, 1, 1);
    matrix_set_ushort(mat, 3, 2, 5);

   // for (int i = 0; i < mat->rows; ++i) {
   //     for (int j = 0; j < mat->cols; ++j) {
			//matrix_set(mat, i, j, generate_random_ushort()); // Initialize remaining elements to random values
   //     }
   // }

    std::cout << "Matrix 2 Initialized, Size:" << mat->rows << " x " << mat->cols << " matrix " << std::endl; // Debug output

    return (unsigned short) 0;
}

void print_matrix(const Matrix* mat, int print_type) {
    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->cols; ++j) {
            if (print_type == MATRIX_TYPE_OPERAND) {
                std::cout << matrix_get_ushort(mat, i, j) << " "; // Print as double
            }
            else if (print_type == MATRIX_TYPE_RESULT) {
                std::cout << matrix_get_uint(mat, i, j) << " "; // Print as long
            } else {
                std::cerr << "Unknown print type!" << std::endl;
                return;
			}
        }
        std::cout << "\n";
    }
}

/*
int main() {

    //int mat1_row_count = 2;
    //int mat1_col_count = 4;
    //    
    //int mat2_row_count = 4;
    //int mat2_col_count = 3;

    int mat1_row_count = 20;
    int mat1_col_count = 25;

    int mat2_row_count = 25;
    int mat2_col_count = 20;
        
        // Create 2x3 matrix (initialized to zeros)
    Matrix* mat1 = matrix_create(mat1_row_count, mat1_col_count);
    if (!mat1) {
        std::cerr << "Matrix allocation failed!" << std::endl;
        return 1;
    }

    Matrix* mat2 = matrix_create(mat2_row_count, mat1_col_count);
    if (!mat2) {
        std::cerr << "Matrix allocation failed!" << std::endl;
        return 1;
    }

    Matrix* mat_result = matrix_create(mat1_row_count, mat2_col_count);
    if (!mat_result) {
        std::cerr << "Matrix allocation failed!" << std::endl;
        return 1;
	}

    unsigned short result;
   
    result = init_matrix1(mat1);
    result = init_matrix2(mat2);

    // Read values
	std::cout << "Matrix 1:\n";
    for (int i = 0; i < mat1_row_count; ++i) {
        for (int j = 0; j < mat1_col_count; ++j) {
            std::cout << matrix_get(mat1, i, j) << " ";
        }
        std::cout << "\n";
    }

    // Read values
	std::cout << "Matrix 2:\n";
    for (int i = 0; i < mat2_row_count; ++i) {
        for (int j = 0; j < mat2_col_count; ++j) {
            std::cout << matrix_get(mat2, i, j) << " ";
        }
        std::cout << "\n";
    }

    // Perform matrix multiplication
	
	unsigned int mul_result = matrix_MatrixMultiply2(mat1, mat2, mat_result);
    // Read values
    std::cout << "Matrix Result:\n";
    for (int i = 0; i < mat_result->rows; ++i) {
        for (int j = 0; j < mat_result->cols; ++j) {
            std::cout << matrix_getlong(mat_result, i, j) << " ";
        }
        std::cout << "\n";
    }

    // Free memory
    matrix_free(mat1);
	matrix_free(mat2);
	matrix_free(mat_result);
       
 //   int counter_max = 100;
 //   for (int counter = 0; counter < counter_max; ++counter) {
 //       unsigned short int random_value = generate_random_ushort();
 //       std::cout << "Random value: " << random_value << std::endl;
	//}

    return 0;
}
 */


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

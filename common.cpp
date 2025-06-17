
#include <iostream>
#include <cstdlib>   // For malloc, calloc, free
#include <stdlib.h>
#include <stdexcept> // For std::out_of_range
#include "MatMul.h"
#include "common.h"


// Safe element access with bounds checking
double matrix_get_ushort(const Matrix* m, int row, int col) {
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return m->ushort_data[row * m->cols + col];
}

// Safe element access with bounds checking
double matrix_get_uint(const Matrix* m, int row, int col) {
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return m->uint_data[row * m->cols + col];
}

// Safe element modification with bounds checking
void matrix_set_ushort(Matrix* m, int row, int col, unsigned short int value) {
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    m->ushort_data[row * m->cols + col] = value;
}

// Safe element modification with bounds checking
void matrix_set_uint(Matrix* m, int row, int col, unsigned short int value) {
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    m->uint_data[row * m->cols + col] = value;
}

int print_message(int message_type, char* message) {
	
	if (message_type == MSG_SYSTEM_OUTPUT ) {
		printf(message);  // Simple string
		return 0;
	}
	else if (message_type == MSG_ERROR_OUTPUT) {
		fprintf(stderr, "Error: %s\n", message);
		return -1;
	}
	else {

		return -1;
	}

}

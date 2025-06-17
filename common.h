#pragma once
#ifndef COMMON_H
#define COMMON_H

#define MSG_SYSTEM_OUTPUT 0
#define MSG_ERROR_OUTPUT 1

#define MATRIX_TYPE_OPERAND 0
#define MATRIX_TYPE_RESULT 1

#define MAX_OPERATION_COUNT 1000
#define MAX_MATRIX_ROW_COUNT 1000
#define MAX_MATRIX_COL_COUNT 1000

struct Matrix {
	unsigned short int matrix_id; // Unique identifier for the matrix
	unsigned short int operand_id; // Identifier for the operand
    unsigned short int rows;
    unsigned short int cols;
    unsigned short int* ushort_data;
    unsigned int* uint_data;
	unsigned int matrix_type ; // default to operand type
    //unsigned short int data[rows][cols]; // Using a 2D array for simplicity, but this is not dynamic
};

struct Operation {
    unsigned short int operation_id; // Unique identifier for the operation
	Matrix* operand1;   // Pointer to the first operand matrix
    Matrix* operand2;   // Pointer to the second operand matrix
    Matrix* result;     // Pointer to the result matrix
};

struct MatrixHeader {
    unsigned short int matrix_id; // Unique identifier for the matrix
    unsigned short int operand_id; // Identifier for the operand
    unsigned short int rows;
    unsigned short int cols;
    unsigned short int matrix_type; // default to operand type
};

double matrix_get_ushort(const Matrix* m, int row, int col); 

double matrix_get_uint(const Matrix* m, int row, int col);

void matrix_set_ushort(Matrix* m, int row, int col, unsigned short int value);

void matrix_set_uint(Matrix* m, int row, int col, unsigned short int value); 

int print_message(int message_type, char* message);


#endif
#include <stdio.h>
#include <stdlib.h>


#include "common.h"
#include "MatMul.h"

FILE* open_file(const char* filename, const char* mode ) {

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, filename, mode);
	if (err != 0) {
		printf("Error opening file: %d\n", err);
		return nullptr;
	}
	else {
		printf("File opening success %d\n", err);
		return fp;
	}
}

MatrixHeader extract_matrix_header(char* buffer) {
	struct MatrixHeader header;
	int result = sscanf_s(buffer, "[%hu,%hu,%hu,%hu,%hu\n", &header.matrix_id, &header.operand_id, &header.rows, &header.cols, &header.matrix_type);
	printf("Parsed data: Matrix Id:%d, Operand Id:%d, Row Count:%d, Column Count:%d, Matrix Type:%d\n", header.matrix_id, header.operand_id, header.rows, header.cols, header.matrix_type);

	return header;
}

Matrix* extract_matrix_operand1() {
	return NULL; // placeholder, should return a valid Matrix pointer

}

Matrix* extract_matrix_operand2() {
	return NULL; // placeholder, should return a valid Matrix pointer
}

Matrix* extract_matrix_result() {

	return NULL; // placeholder, should return a valid Matrix pointer
}

int matrix_release(Matrix* mat) {
	if (mat != NULL) {
		if (mat->ushort_data != NULL) {
			free(mat->ushort_data); // free the data array
		}
		if (mat->uint_data != NULL) {
			free(mat->uint_data); // free the data array
		}
		free(mat); // free the matrix object itself
		return 0; // return success
	}
	return 1; // return failure if mat is NULL
}

int release_operations(Operation* operations) {

	if (operations != NULL) {
		for (int i = 0; i < sizeof(operations); i++) {
			Matrix* operand1 = operations[i].operand1;
			Matrix* operand2 = operations[i].operand2;
			Matrix* result = operations[i].result;
			if (operand1 != NULL) {
				matrix_release(operand1); // release the first operand matrix
			}
			if (operand2 != NULL) {
				matrix_release(operand2); // release the second operand matrix
			}
			if (result != NULL) {
				matrix_release(result); // release the result matrix
			}
			free(&operations[i]); // free the operation structure
		}

		return 0; // return success
	}
	return 1; // return failure if mat is NULL
}

// read matrix from file and print it to console
 static int read_matrix(const char* filename) {

	FILE* fp = open_file(filename, "r");

	struct Operation operations[MAX_OPERATION_COUNT];
		
	char buff[65336];
	while (fgets(buff, sizeof(buff), fp) != NULL) { // read the first line which contains the matrix header
		
		//printf("Read data: %s\n", fgets(buff, 256, fp));

		// extract matrix header
		//int matrix_id, operand_id, rows, cols, matrix_type;
		//int result = sscanf_s(buff, "[%d,%d,%d,%d,%d\n", &matrix_id, &operand_id, &rows, &cols, &matrix_type);
		//printf("Parsed data: Matrix Id:%d, Operand Id:%d, Row Count:%d, Column Count:%d, Matrix Type:%d\n", matrix_id, operand_id, rows, cols, matrix_type);
		
		MatrixHeader header = extract_matrix_header(buff);

		// create a matrix object using the parsed data
		Matrix* mat = matrix_create(header.matrix_id, header.operand_id, header.rows, header.cols, header.matrix_type);

		// extract matrix data
			// iterate over M rows
		for (int i = 0; i < header.rows; i++) {
			//printf("Row %d: \n", i);
			//	// read one line from the file which is one row of the matrix
			char row_line[2048];
			fgets(row_line, sizeof(row_line), fp);
			printf("%s", row_line);

			unsigned short	ushort_data;
			unsigned int	uint_data;

			// iterate over N columns
			for (int j = 0; j < header.cols; j++) {
				//printf("Column %d, ", j);
				//		// read the next value from the file
				if (header.matrix_type == MATRIX_TYPE_OPERAND) {
					int res = sscanf_s(row_line, "%hu{,\n]}", &ushort_data);
					matrix_set_ushort(mat, i, j, ushort_data);
				}
				else if (header.matrix_type == MATRIX_TYPE_RESULT) {
					int res = sscanf_s(row_line, "%d{,\n]}", &uint_data);
					matrix_set_uint(mat, i, j, uint_data);
				}
				else {
					printf("Unknown matrix type: %d\n", header.matrix_type);
					fclose(fp);
					free(mat);
					return 1;
				}
			}
			//printf("\n");

			// read rows and columns
			// initialize matrix
			// iterate row-major order then column-major order
			// populate the matrix data
		}

	} // end of while loop

	// clean up
	fclose(fp);
	//release_operations(operations); // release the operations array

	return 0; // return success
}

//int main() {
//	// This is a simple C++ program that does nothing.
//	return read_matrix("MatrixSample.txt");
//
//	//return 0;
//}
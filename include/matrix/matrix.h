#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "matrix_error.h"

typedef void (*BinaryOperator)(void* result, void* arg1, void* arg2);

typedef struct {
    size_t size;
    BinaryOperator add;
    BinaryOperator multiply;
    void (*mult_const)(void*, void*, int);
    void (*print)(void*);
} TypeInfo;

typedef struct {
    void* data;               
    size_t razm;              
    TypeInfo* typeInfo;
} Matrix;

Matrix* matrix_create(int razm, TypeInfo* typeInfo, MatrixErrors* operationResult);
MatrixErrors push_el_matrix(Matrix* mat, void* item, int row, int col);
void* element_get(Matrix* mat, int row, int col, MatrixErrors* operationResult);
Matrix* matrix_add(Matrix* mat_1, Matrix* mat_2, MatrixErrors* operationResult);
Matrix* matrix_mult(Matrix* mat_1, Matrix* mat_2, MatrixErrors* operationResult);
Matrix* matrix_transp(Matrix* mat_1, MatrixErrors* operationResult);
MatrixErrors matrix_multiply_const(Matrix* mat_1, int alhpa);
MatrixErrors print_matrix(Matrix* mat);
void matrix_free(Matrix* mat);

#endif //MATRIX_H
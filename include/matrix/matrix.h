#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

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

Matrix* matrix_create(int razm, TypeInfo* typeInfo);
void push_el_matrix(Matrix* mat, void* item, int row, int col);
void* element_get(Matrix* mat, int row, int col);
Matrix* matrix_add(Matrix* mat_1, Matrix* mat_2);
Matrix* matrix_mult(Matrix* mat_1, Matrix* mat_2);
Matrix* matrix_transp(Matrix* mat_1);
void matrix_multiply_const(Matrix* mat_1, int alhpa);
void print_matrix(Matrix* mat);
void matrix_free(Matrix* mat);

#endif //MATRIX_H
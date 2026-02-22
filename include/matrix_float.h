#ifndef MATRIX_FLOAT_H
#define MATRIX_FLOAT_H

#include "matrix.h"
#include <stdio.h>

void print_float(void* element) {
    printf("%d", *(float *)element);
}

void add_float(void* result, void* a, void* b) {
    *(float *)result = *(float *)a + *(float *)b;
}

void mult_float(void* a, void* b) {
    (*(float *)a * *(float *)b);
}

Matrix* create_int_matrix(size_t rows, size_t cols) {
    return matrix_create(rows, cols, sizeof(float), print_float, add_float, mult_float);
}

#endif //MATRIX_FLOAT_H
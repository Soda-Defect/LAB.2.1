#ifndef MATRIX_INT_H
#define MATRIX_INT_H

#include "matrix.h"
#include <stdio.h>

void print_int(void* element) {
    printf("%d", *(int *)element);
}

void add_int(void* result, void* a, void* b) {
    *(int *)result = *(int *)a + *(int *)b;
}

void mult_int(void* result, void* a, void* b) {
    *(int *)result = (*(int *)a * *(int *)b);
}

Matrix* create_int_matrix(size_t rows, size_t cols) {
    return matrix_create(rows, cols, sizeof(int), print_int, add_int, mult_int);
}

#endif //MATRIX_INT_H
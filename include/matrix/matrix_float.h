#ifndef MATRIX_FLOAT_H
#define MATRIX_FLOAT_H

#include "matrix.h"
#include <stdio.h>

void print_float(void* element) {
    printf("%4.2f", *(float *)element);
}

void add_float(void* result, void* a, void* b) {
    *(float *)result = *(float *)a + *(float *)b;
}

void mult_float(void* result, void* a, void* b) {
    *(float *)result = (*(float *)a * *(float *)b);
}

Matrix* create_float_matrix(size_t razm) {
    return matrix_create(razm, sizeof(float), print_float, add_float, mult_float);
}

#endif //MATRIX_FLOAT_H
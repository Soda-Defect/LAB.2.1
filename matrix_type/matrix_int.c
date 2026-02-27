#include <stdio.h>
#include "../include/matrix/matrix.h"
#include "../include/matrix/matrix_int.h"

void print_int(void* element) {
    printf("%4.d", *(int *)element);
}

void add_int(void* result, void* a, void* b) {
    *(int *)result = *(int *)a + *(int *)b;
}

void mult_int(void* result, void* a, void* b) {
    *(int *)result = (*(int *)a * *(int *)b);
}

Matrix* create_int_matrix(size_t razm) {
    return matrix_create(razm, sizeof(int), print_int, add_int, mult_int);
}
#ifndef MATRIX_FLOAT_H
#define MATRIX_FLOAT_H

void print_float(void* element);
void add_float(void* result, void* a, void* b);
void mult_float(void* result, void* a, void* b);
void mult_float_const(void* result, void* a, int b);
Matrix* create_float_matrix(size_t razm);

#endif //MATRIX_FLOAT_H
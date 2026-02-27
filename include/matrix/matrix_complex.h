#ifndef MATRIX_COMPLEX_H
#define MATRIX_COMPLEX_H

void print_complex(void* element);
void add_complex(void* result, void* a, void* b);
void mult_complex(void* result, void* a, void* b);
Matrix* create_complex_matrix(size_t razm);

#endif //MATRIX_COMPLEX_H

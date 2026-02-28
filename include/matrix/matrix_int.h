#ifndef MATRIX_INT_H
#define MATRIX_INT_H

inline void print_int(void* element);
inline void add_int(void* result, void* a, void* b);
inline void mult_int(void* result, void* a, void* b);
void mult_int_const(void* result, void* a, int b);
Matrix* create_int_matrix(size_t razm);

#endif //MATRIX_INT_H
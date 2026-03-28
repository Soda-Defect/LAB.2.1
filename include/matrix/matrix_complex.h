#ifndef MATRIX_COMPLEX_H
#define MATRIX_COMPLEX_H

void print_complex(void* element);
void add_complex(void* result, void* a, void* b);
void mult_complex(void* result, void* a, void* b);
void mult_complex_const(void* result, void* a, int b);
TypeInfo* GetComplexTypeInfo();

#endif //MATRIX_COMPLEX_H

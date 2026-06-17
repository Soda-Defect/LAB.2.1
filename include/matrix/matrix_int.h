#ifndef MATRIX_INT_H
#define MATRIX_INT_H

void print_int(void* element);
void add_int(void* result, void* a, void* b);
void mult_int(void* result, void* a, void* b);
void mult_int_const(void* result, void* a, int b);
TypeInfo* GetIntTypeInfo();

#endif //MATRIX_INT_H
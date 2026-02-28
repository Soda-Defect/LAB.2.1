#include "../include/complex.h"
#include "../include/matrix/matrix.h"
#include "../include/matrix/matrix_complex.h"

void print_complex(void* element) {
    Complex* c = (Complex *)element;
    complex_print(*c);
}

void add_complex(void* result, void* a, void* b) {
    Complex* c1 = (Complex *)a;
    Complex* c2 = (Complex *)b;
    Complex* res = (Complex *)result;

    *res = complex_add(*c1, *c2);
}

void mult_complex(void* result, void* a, void* b) {
    Complex* c1 = (Complex *)a;
    Complex* c2 = (Complex *)b;
    Complex* res = (Complex *)result;

    *res = complex_mul(*c1, *c2);
}

void mult_complex_const(void* result, void* a, int b) {
    Complex* c1 = (Complex *)a;
    Complex* res = (Complex *)result;
    res->real =c1->real * b;
    res->imag =c1->imag  * b;
}

Matrix* create_complex_matrix(size_t razm) {
    return matrix_create(razm, sizeof(Complex), print_complex, add_complex, mult_complex, mult_complex_const);
}
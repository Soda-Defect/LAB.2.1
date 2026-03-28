#include "../include/complex.h"
#include "../include/matrix/matrix.h"
#include "../include/matrix/matrix_complex.h"

static TypeInfo* COMPLEX_TYPE_INFO = NULL;

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

TypeInfo* GetComplexTypeInfo() {
    if (COMPLEX_TYPE_INFO == NULL) {
        COMPLEX_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        COMPLEX_TYPE_INFO->size = sizeof(Complex);
        COMPLEX_TYPE_INFO->add = add_complex;
        COMPLEX_TYPE_INFO->multiply = mult_complex; 
        COMPLEX_TYPE_INFO->mult_const = mult_complex_const;
        COMPLEX_TYPE_INFO->print = print_complex;
    }
    return COMPLEX_TYPE_INFO;
}
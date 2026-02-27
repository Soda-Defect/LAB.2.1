#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

typedef struct {
    int real; //действительная часть
    int imag; //мнимая часть
} Complex;

Complex complex_create(int real, int imag);
Complex complex_add(Complex a, Complex b);
Complex complex_mul(Complex a, Complex b);
void complex_print(Complex c);

#endif //COMPLEX_H

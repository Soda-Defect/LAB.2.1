#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

typedef struct {
    double real; //действительная часть
    double imag; //мнимая часть
} Complex;

Complex complex_create(double real, double imag);
Complex complex_add(Complex a, Complex b);
Complex complex_mul(Complex a, Complex b);
void complex_print(Complex c);

#endif //COMPLEX_H
